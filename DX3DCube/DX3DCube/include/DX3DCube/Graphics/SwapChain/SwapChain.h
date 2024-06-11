#pragma once
#include <d3d11.h>


class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool Initialize(HWND hwnd, UINT width, UINT height);
	bool Present(bool vsync);
	bool Release();

private:
	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;


	friend class DeviceContext;
};

