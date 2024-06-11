#pragma once
#include <d3d11.h>


class DeviceContext;

class VertexBuffer
{
private:
	UINT m_sizeVertex;
	UINT m_sizeList;


	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;


	friend class DeviceContext;


public:
	VertexBuffer();
	~VertexBuffer();

	bool Load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader);
	bool Release();
	UINT GetSizeVertexList();
};

