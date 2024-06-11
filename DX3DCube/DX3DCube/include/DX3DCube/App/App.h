#pragma once

#include <memory>
#include <DX3DCube/Window/Window.h>
#include <DX3DCube/Graphics/GraphicsEngine.h>
#include <DX3DCube/Graphics/SwapChain/SwapChain.h>
#include <DX3DCube/Graphics/DeviceContext/DeviceContext.h>
#include <DX3DCube/Graphics/VertexBuffer/VertexBuffer.h>
#include <DX3DCube/Graphics/IndexBuffer/IndexBuffer.h>
#include <DX3DCube/Graphics/ConstantBuffer/ConstantBuffer.h>
#include <DX3DCube/Graphics/VertexShader/VertexShader.h>
#include <DX3DCube/Graphics/PixelShader/PixelShader.h>
#include <DX3DCube/Input/InputListener.h>


class App : public Window, public InputListener
{
private:
	SwapChain* m_swapChain;
	VertexBuffer* m_vertexBuffer;
	IndexBuffer* m_indexBuffer;
	VertexShader* m_vertexShader;
	PixelShader* m_pixelShader;
	ConstantBuffer* m_constantBuffer;


	ULONGLONG m_oldDelta;
	ULONGLONG m_newDelta;
	double m_deltaTime;

	double m_deltaPosition;
	double m_deltaScale;
	double m_deltaRotation;

	double m_rotationX = 0.0;
	double m_rotationY = 0.0;


public:
	App();
	~App();

	void UpdateQuadPosition();

	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;


	void OnKeyDown(int key) override;
	void OnKeyUp(int key) override;
};


