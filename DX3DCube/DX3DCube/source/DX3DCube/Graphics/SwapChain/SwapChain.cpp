#include <DX3DCube/Graphics/SwapChain/SwapChain.h>
#include <DX3DCube/Graphics/GraphicsEngine.h>

SwapChain::SwapChain()
{
}

bool SwapChain::Initialize(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::Get()->m_d3dDevice;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;


	HRESULT result = GraphicsEngine::Get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swapChain);

	if (FAILED(result))
	{
		return false;
	}

	ID3D11Texture2D* buffer = NULL;
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(result))
	{
		return false;
	}

	result = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool SwapChain::Present(bool vsync)
{
	m_swapChain->Present(vsync, NULL);

	return true;
}

bool SwapChain::Release()
{
	m_swapChain->Release();

	delete this;
	return true;
}

SwapChain::~SwapChain()
{
}
