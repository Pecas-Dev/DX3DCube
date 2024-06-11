#include <DX3DCube/Graphics/DeviceContext/DeviceContext.h>
#include <DX3DCube/Graphics/SwapChain/SwapChain.h>
#include <DX3DCube/Graphics/VertexBuffer/VertexBuffer.h>
#include <DX3DCube/Graphics/IndexBuffer/IndexBuffer.h>
#include <DX3DCube/Graphics/ConstantBuffer/ConstantBuffer.h>
#include <DX3DCube/Graphics/VertexShader/VertexShader.h>
#include <DX3DCube/Graphics/PixelShader/PixelShader.h>


DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) :m_deviceContext(device_context)
{
}

void DeviceContext::ClearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = {
		red,
		green,
		blue,
		alpha };

	m_deviceContext->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
	m_deviceContext->OMSetRenderTargets(1, &swap_chain->m_rtv, NULL);
}

void DeviceContext::SetVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT stride = vertex_buffer->m_sizeVertex;
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
	m_deviceContext->IASetInputLayout(vertex_buffer->m_layout);
}

void DeviceContext::SetIndexBuffer(IndexBuffer* index_buffer)
{
	m_deviceContext->IASetIndexBuffer(index_buffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::DrawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::DrawIndexedTriangleList(UINT index_count, UINT start_vertexIndex, UINT start_indexLocation)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->DrawIndexed(index_count, start_indexLocation, start_vertexIndex);

}

void DeviceContext::DrawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_deviceContext->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::SetViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	m_deviceContext->RSSetViewports(1, &viewport);
}

void DeviceContext::SetVertexShader(VertexShader* vertex_shader)
{
	m_deviceContext->VSSetShader(vertex_shader->m_vs, nullptr, 0);
}

void DeviceContext::SetPixelShader(PixelShader* pixel_shader)
{
	m_deviceContext->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}

void DeviceContext::SetConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer)
{
	m_deviceContext->VSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

void DeviceContext::SetConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer)
{
	m_deviceContext->PSSetConstantBuffers(0, 1, &buffer->m_buffer);
}


bool DeviceContext::Release()
{
	m_deviceContext->Release();

	delete this;
	return true;
}

DeviceContext::~DeviceContext()
{
}