#include <DX3DCube/Graphics/GraphicsEngine.h>
#include <DX3DCube/Graphics/SwapChain/SwapChain.h>
#include <DX3DCube/Graphics/DeviceContext/DeviceContext.h>
#include <DX3DCube/Graphics/VertexBuffer/VertexBuffer.h>
#include <DX3DCube/Graphics/IndexBuffer/IndexBuffer.h>
#include <DX3DCube/Graphics/ConstantBuffer/ConstantBuffer.h>
#include <DX3DCube/Graphics/VertexShader/VertexShader.h>
#include <DX3DCube/Graphics/PixelShader/PixelShader.h>


#include <d3dcompiler.h>


GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::Initialize()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);


	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);


	HRESULT result = 0;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3dDevice, &m_featureLevel, &m_imm_context);

		if (SUCCEEDED(result))
		{
			break;
			++driver_type_index;
		}

	}

	if (FAILED(result))
	{
		return false;
	}

	m_imm_device_context = new DeviceContext(m_imm_context);

	m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}


bool GraphicsEngine::Release()
{
	if (m_vs)
	{
		m_vs->Release();
	}

	if (m_ps)
	{
		m_ps->Release();
	}

	if (m_vsblob)
	{
		m_vsblob->Release();
	}

	if (m_psblob)
	{
		m_psblob->Release();
	}

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_device_context->Release();
	m_d3dDevice->Release();

	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

SwapChain* GraphicsEngine::CreateSwapChain()
{
	return new SwapChain();
}


DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer();
}

IndexBuffer* GraphicsEngine::CreateIndexBuffer()
{
	return new IndexBuffer();
}

ConstantBuffer* GraphicsEngine::CreateConstantBuffer()
{
	return new ConstantBuffer();
}

VertexShader* GraphicsEngine::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vertexShader = new VertexShader();

	if (!vertexShader->Initialize(shader_byte_code, byte_code_size))
	{
		vertexShader->Release();
		return nullptr;
	}

	return vertexShader;
}

PixelShader* GraphicsEngine::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* pixelShader = new PixelShader();

	if (!pixelShader->Init(shader_byte_code, byte_code_size))
	{
		pixelShader->Release();
		return nullptr;
	}

	return pixelShader;
}

bool GraphicsEngine::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;

	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();

		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;

	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();

		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::ReleaseCompiledShader()
{
	if (m_blob)m_blob->Release();
}

GraphicsEngine* GraphicsEngine::Get()
{
	static GraphicsEngine engine;
	return &engine;
}
