#include "DXSample.h"

using namespace Microsoft::WRL;

DXSample::DXSample(int width, int height, const std::string name)
    : width_{width}
    , height_{height}
    , title_{name}
    , aspectRatio_{static_cast<float>(width) / static_cast<float>(height)}
{}

DXSample::~DXSample() {}

void DXSample::GetHardwareAdapter(IDXGIFactory1* pFactory, IDXGIAdapter1** ppAdapter, bool requestHighPerformanceAdapter)
{

    *ppAdapter = nullptr;
    ComPtr<IDXGIAdapter1> adapter;
    ComPtr<IDXGIFactory6> factory6;
    DXGI_GPU_PREFERENCE   gpuReferenceType =
        requestHighPerformanceAdapter ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_UNSPECIFIED;
    if (SUCCEEDED(pFactory->QueryInterface(IID_PPV_ARGS(&factory6)))) {
        for (uint32_t adapterIndex = 0;
             SUCCEEDED(factory6->EnumAdapterByGpuPreference(adapterIndex, gpuReferenceType, IID_PPV_ARGS(&adapter)));
             ++adapterIndex) {
            DXGI_ADAPTER_DESC1 desc;
            adapter->GetDesc1(&desc);
            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
                continue;
            }

            if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_2, __uuidof(ID3D12Device), nullptr))) {
                break;
            }
        }
    }

    *ppAdapter = adapter.Detach();
}
