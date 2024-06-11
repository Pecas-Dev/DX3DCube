#include <DX3DCube/Graphics/VertexBuffer/VertexBuffer.h>
#include <DX3DCube/Graphics/GraphicsEngine.h>



VertexBuffer::VertexBuffer() :m_layout(0), m_buffer(0)
{
}

bool VertexBuffer::Load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
	if (m_buffer)
	{
		m_buffer->Release();
	}

	if (m_layout)
	{
		m_layout->Release();
	}

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	m_sizeVertex = size_vertex;
	m_sizeList = size_list;

	if (FAILED(GraphicsEngine::Get()->m_d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0,    0,   D3D11_INPUT_PER_VERTEX_DATA,  0 },
		{ "COLOR",   0,  DXGI_FORMAT_R32G32B32_FLOAT, 0,   12,   D3D11_INPUT_PER_VERTEX_DATA,  0 },
		{ "COLOR",   1,  DXGI_FORMAT_R32G32B32_FLOAT, 0,   24,   D3D11_INPUT_PER_VERTEX_DATA,  0 }
	};

	UINT size_layout = ARRAYSIZE(layout);

	if (FAILED(GraphicsEngine::Get()->m_d3dDevice->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
	{
		return false;
	}

	return true;
}

UINT VertexBuffer::GetSizeVertexList()
{
	return this->m_sizeList;
}

bool VertexBuffer::Release()
{
	m_layout->Release();
	m_buffer->Release();

	delete this;
	return true;
}


VertexBuffer::~VertexBuffer()
{
}
