#pragma once
#include <d3d11.h>


class GraphicsEngine;
class DeviceContext;

class VertexShader
{
private:
	ID3D11VertexShader* m_vs;

	bool Initialize(const void* shader_byte_code, size_t byte_code_size);


	friend class GraphicsEngine;
	friend class DeviceContext;


public:
	VertexShader();
	~VertexShader();

	void Release();
};

