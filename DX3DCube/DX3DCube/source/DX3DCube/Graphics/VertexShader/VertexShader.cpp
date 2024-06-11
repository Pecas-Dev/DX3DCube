#include <DX3DCube/Graphics/VertexShader/VertexShader.h>
#include <DX3DCube/Graphics/GraphicsEngine.h>


VertexShader::VertexShader()
{
}

void VertexShader::Release()
{
	m_vs->Release();
	delete this;
}

bool VertexShader::Initialize(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::Get()->m_d3dDevice->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
	{
		return false;
	}


	return true;
}



VertexShader::~VertexShader()
{
}





