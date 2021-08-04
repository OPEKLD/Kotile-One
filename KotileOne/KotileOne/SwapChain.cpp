#include "SwapChain.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	//Pointer to DirectX device (needed for swap chain creation
	ID3D11Device* device = GraphicsEngine::get()->m_dx3_device;
	//DXGI swap chain desc
	DXGI_SWAP_CHAIN_DESC desc;
	//Fill memory of desc with zero to avoid errors
	ZeroMemory(&desc, sizeof(desc));
	//Set buffer count to 1. Direct X uses 2 buffers, but one is already in cpu's screen therefore only one needs to be generated
	desc.BufferCount = 1;
	//Width and height
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	//Set format for pixels (chosen one is 8 bits per each pixels)
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	//Treat buffer as render targets
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//Tell buffer what window to use
	desc.OutputWindow = hwnd;

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	//Enable Windowed mode
	desc.Windowed = TRUE;
	
	//Create the swap chain
	HRESULT hr = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		return false;
	}
	
	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	
	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, NULL);
	
	return true;
}

bool SwapChain::release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}

SwapChain::~SwapChain()
{
}
