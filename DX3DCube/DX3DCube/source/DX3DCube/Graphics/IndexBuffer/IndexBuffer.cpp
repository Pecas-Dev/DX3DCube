#include <DX3DCube/Graphics/IndexBuffer/IndexBuffer.h>
#include <DX3DCube/Graphics/GraphicsEngine.h>

IndexBuffer::IndexBuffer() : m_buffer(0)
{
}

IndexBuffer::~IndexBuffer()
{
}

bool IndexBuffer::Load(void* list_indices, UINT size_list)
{
	if (m_buffer)
	{
		m_buffer->Release();
	}


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = 4 * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_indices;

	m_sizeList = size_list;

	if (FAILED(GraphicsEngine::Get()->m_d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	return true;
}

UINT IndexBuffer::GetSizeIndexList()
{
	return m_sizeList;
}

bool IndexBuffer::Release()
{
	m_buffer->Release();

	delete this;
	return true;
}


