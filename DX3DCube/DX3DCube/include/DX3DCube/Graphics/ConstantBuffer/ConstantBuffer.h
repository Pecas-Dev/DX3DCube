#pragma once
#include <d3d11.h>


class DeviceContext;

class ConstantBuffer
{
private:
	ID3D11Buffer* m_buffer;


	friend class DeviceContext;


public:
	ConstantBuffer();
	~ConstantBuffer();

	bool Load(void* buffer, UINT size_buffer);
	bool Release();

	void Update(DeviceContext* context, void* buffer);
};

