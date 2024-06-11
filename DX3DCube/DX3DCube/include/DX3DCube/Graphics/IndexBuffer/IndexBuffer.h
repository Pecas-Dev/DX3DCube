#pragma once
#include <d3d11.h>

class DeviceContext;

class IndexBuffer
{
private:
	UINT m_sizeList;
	ID3D11Buffer* m_buffer;


	friend class DeviceContext;

public:
	IndexBuffer();
	~IndexBuffer();

	bool Load(void* list_indices,  UINT size_list);
	bool Release();
	UINT GetSizeIndexList();
};

