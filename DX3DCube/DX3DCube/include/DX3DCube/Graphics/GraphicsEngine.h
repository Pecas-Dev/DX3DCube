#pragma once
#include <d3d11.h>


class SwapChain;
class DeviceContext;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;

class GraphicsEngine
{
private:
	DeviceContext* m_imm_device_context;
	ID3D11Device* m_d3dDevice;
	D3D_FEATURE_LEVEL m_featureLevel;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;


	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;


	ID3DBlob* m_blob = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class IndexBuffer;


public:
	GraphicsEngine();
	~GraphicsEngine();

	bool Initialize();
	bool Release();


	SwapChain* CreateSwapChain();
	DeviceContext* GetImmediateDeviceContext();
	VertexBuffer* CreateVertexBuffer();
	IndexBuffer* CreateIndexBuffer();
	ConstantBuffer* CreateConstantBuffer();
	VertexShader* CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShader* CreatePixelShader(const void* shader_byte_code, size_t byte_code_size);

	bool CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

	void ReleaseCompiledShader();


	static GraphicsEngine* Get();
};

