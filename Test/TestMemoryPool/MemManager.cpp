
#include "MemManager.h"
#include <iostream>

namespace SP {

	MemWin32* MemWin32::_instance = new MemWin32();

	MemWin32::MemWin32()
	{
		mOsPoolTable.BlockSize = 0;
		mOsPoolTable.excedPool = nullptr;
		mOsPoolTable.FreePool = nullptr;

		mPoolTable[0].FreePool = NULL;
		mPoolTable[0].excedPool = NULL;
		mPoolTable[0].BlockSize = 8;

		for (DWORD i = 1; i < 5; i++)
		{
			mPoolTable[i].FreePool = NULL;
			mPoolTable[i].excedPool = NULL;
			mPoolTable[i].BlockSize = (8 << ((i + 1) >> 2)) + (2 << i);
		}
		for (DWORD i = 5; i < POOL_TABLE_COUNT; i++)
		{
			mPoolTable[i].FreePool = NULL;
			mPoolTable[i].excedPool = NULL;
			mPoolTable[i].BlockSize = (4 + ((i + 7) & 3)) << (1 + ((i + 7) >> 2));
		}

		for (DWORD i = 0; i < POOL_SIZE_MAX; i++)
		{
			DWORD Index;
			for (Index = 0; mPoolTable[Index].BlockSize < i; Index++);
				mMemSizeToPoolTable[i] = &mPoolTable[Index];
		}
		// poolinfo 也需要初始化，要不然是未初始化的值, 也可以用到的时候再初始化
		/*for (size_t i = 0; i < POOL_INFO_COUNT; i++) {
		}*/

	}

	MemWin32::~MemWin32()
	{
	}

	void* MemWin32::Allocate(size_t uiSize, size_t alignment)
	{
		FreeMem* freeAddress;
		if (uiSize < POOL_SIZE_MAX) {
			PoolTable* poolTable = mMemSizeToPoolTable[uiSize];
			if (!poolTable->FreePool) {
				// 申请一页 64 KB 内存
				size_t blocks = ALLOC_SIZE_ONE_PAGE / poolTable->BlockSize;
				size_t bytes = blocks * poolTable->BlockSize;

				freeAddress = (FreeMem*)VirtualAlloc(nullptr, bytes, MEM_COMMIT, PAGE_READWRITE);
				// static_asset
				freeAddress->Blocks = blocks;
				freeAddress->Next = nullptr;
				
				// freeAddress 到 pool 的映射关系
				size_t poolIndex = ((size_t)freeAddress & (0xffff0000)) >> 16;
				mPoolInfo[poolIndex].FirstFree = (FreeMem*)freeAddress;
				mPoolInfo[poolIndex].Next = mPoolInfo[poolIndex].Pre = nullptr;
				mPoolInfo[poolIndex].Table = poolTable;
				mPoolInfo[poolIndex].Mem = (BYTE*)freeAddress;
				mPoolInfo[poolIndex].Token = 0;
				mPoolInfo[poolIndex].Link(poolTable->FreePool);
			}

			PoolInfo* poolInfo = poolTable->FreePool;
			poolInfo->Token++;
			freeAddress = (FreeMem*)((byte*)poolInfo->FirstFree + --poolInfo->FirstFree->Blocks * poolTable->BlockSize);
			if (poolInfo->FirstFree->Blocks == 0) {
				if (poolInfo->FirstFree->Next) {
					poolInfo->FirstFree = poolInfo->FirstFree->Next;
				}
				else {
					poolInfo->FirstFree = nullptr;
					poolInfo->UnLink();
					poolInfo->Link(poolTable->excedPool);
				}
				
			}
		}
		else {  // os table
			
			freeAddress = (FreeMem*)VirtualAlloc(nullptr, uiSize, MEM_COMMIT, PAGE_READWRITE);
			auto poolIndex = ((size_t)freeAddress & (0xffff0000)) >> 16;
			mPoolInfo[poolIndex].FirstFree = nullptr;
			mPoolInfo[poolIndex].Next = mPoolInfo[poolIndex].Pre = nullptr;
			mPoolInfo[poolIndex].Table = &mOsPoolTable;
			mPoolInfo[poolIndex].Mem = (BYTE*)freeAddress;
			mPoolInfo[poolIndex].Token = 1;
		}
		return freeAddress;
	}

	void MemWin32::Deallocate(BYTE* ptr, size_t alignment)
	{
		if (!ptr) {
			return;
		}

		size_t poolIndex = (((size_t)ptr & (0xffff0000)) >> 16);
		PoolInfo* poolInfo = &mPoolInfo[poolIndex];
		if (poolInfo->Table != &mOsPoolTable) {
			if (!poolInfo->FirstFree) {
				poolInfo->UnLink();
				poolInfo->Link(poolInfo->Table->FreePool);
			}

			FreeMem* freeMem = (FreeMem*)ptr;
			freeMem->Blocks = 1;
			freeMem->Next = poolInfo->FirstFree;
			poolInfo->FirstFree = freeMem;

			if (--poolInfo->Token == 0) {
				// 回收整个pool


				poolInfo->UnLink();
				VirtualFree(poolInfo->Mem, 0, MEM_RELEASE);
				poolInfo->Mem = nullptr;
			

			}
		}
		else {
			VirtualFree(poolInfo->Mem, 0, MEM_RELEASE);
			poolInfo->Mem = nullptr;
		}
	}

	void MemWin32::PrintInfo() {
		for (int i = 0; i < POOL_TABLE_COUNT; i++) {
			std::cout << mPoolTable[i].BlockSize << std::endl;

		}
	}

}



