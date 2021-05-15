#pragma once
#include <Windows.h>
#include <new.h>


#define POOL_TABLE_COUNT 42
#define POOL_INFO_COUNT 65532
#define ALLOC_SIZE_ONE_PAGE  65532
#define POOL_SIZE_MAX (POOL_INFO_COUNT / 2 + 1)

#define USE_CUSTOM_MALLOC

namespace SP {

	template <typename T>
	FORCEINLINE T Align(const T t, size_t alignment) {
		return (T)(((size_t)t + alignment - 1) & ~(alignment - 1));
	}


	class MemManager {
		virtual void* Allocate(size_t uiSize, size_t alignment) { return nullptr; }
		virtual void Deallocate(BYTE * ptr, size_t alignment){}
	};

	class MemWin32 : public MemManager {
	public:
		MemWin32();
		~MemWin32();
		virtual void* Allocate(size_t uiSize, size_t alignment);
		virtual void Deallocate(BYTE* ptr, size_t alignment);

		static MemWin32* _instance;
		static MemWin32& Instance() { return *MemWin32::_instance; };

		void PrintInfo();

	private:
		struct FreeMem;
		struct PoolTable;
		struct PoolInfo {
			DWORD Token;
			BYTE* Mem;
			PoolTable* Table;
			FreeMem* FirstFree;
			PoolInfo* Next;
			PoolInfo* Pre;
			// head 是 table 中的 FreePool
			void Link(PoolInfo*& before) {
				if (before) {
					if (before->Pre) {
						before->Pre->Next = this;
					}
					this->Pre = before->Pre;
				}
				else
					this->Pre = nullptr;
				this->Next = before;
				before = this;
			}
			void UnLink() {
				if (Table) {
					if (Table->excedPool == this) {
						Table->excedPool = this->Next;
					}

					if (Table->FreePool == this) {
						Table->FreePool = this->Next;
					}

				}

				if (this->Pre) {
					this->Pre->Next = this->Next;
				}
				if (this->Next) {
					this->Next->Pre = this->Pre;
				}
			}
		};
		
		struct FreeMem {
			FreeMem* Next;
			size_t Blocks;
			PoolInfo* GetPool();
		};

		struct PoolTable {
			PoolInfo* FreePool;  // 还有空闲的
			PoolInfo* excedPool;  // 已经分配完成的
			size_t BlockSize;  // 它管理的block的大小。 一页是64k，blockSize: 8 - 32768
		};

		PoolTable mPoolTable[POOL_TABLE_COUNT], mOsPoolTable;
		PoolInfo mPoolInfo[POOL_INFO_COUNT];
		PoolTable* mMemSizeToPoolTable[POOL_SIZE_MAX];
	};


	class MemObj {
	public:
		void* operator new (size_t size) {
			auto t = SP::MemWin32::Instance().Allocate(size, 0);
			return t;
		}
		void operator delete(void* ptr) {
			SP::MemWin32::Instance().Deallocate((BYTE*)ptr, 0);
		}
	};
}





//
//#ifdef USE_CUSTOM_MALLOC
//
//FORCEINLINE void* operator new (size_t uiSize) noexcept {
//	//return malloc(uiSize);
//	auto t = SP::MemWin32::Instance().Allocate(uiSize, 0);
//	std::cout << (size_t)t;
//	return t;
//}
//
//FORCEINLINE void* operator new [](size_t uiSize) noexcept {
//	return malloc(uiSize);
//}
//
//FORCEINLINE void operator delete(void* ptr) noexcept {
//	SP::MemWin32::Instance().Deallocate((BYTE*)ptr, 0);
//}
//
//FORCEINLINE void operator delete [](void* ptr) noexcept {
//	free(ptr);
//}


//#endif