#pragma once
#include <d3d11.h>


class GraphicsEngine;
class DeviceContext;

class PixelShader
{
private:
	ID3D11PixelShader* m_ps;


	bool Init(const void* shader_byte_code, size_t byte_code_size);


	friend class GraphicsEngine;
	friend class DeviceContext;


public:
	PixelShader();
	~PixelShader();

	void Release();

};

