#pragma once
#include <d3d11.h>

class SwapChain
{
public:
	SwapChain();
	//Initalize
	bool init(HWND hwnd, UINT width, UINT height);

	//Releasing
	bool release();

	~SwapChain();
private:
	IDXGISwapChain* m_swap_chain;
};

