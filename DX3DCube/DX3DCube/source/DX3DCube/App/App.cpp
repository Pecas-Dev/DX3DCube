#include <DX3DCube/App/App.h>
#include <Windows.h>
#include <DX3DCube/Math/Vector3D.h>
#include <DX3DCube/Math/Matrix4x4.h>
#include <DX3DCube/Input/InputSystem.h>

struct Vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};


__declspec(align(16))

struct constant
{
	Matrix4x4 m_world = {};
	Matrix4x4 m_view = {};
	Matrix4x4 m_proj = {};
	ULONGLONG m_time = {};
};

App::App()
{
}

void App::UpdateQuadPosition()
{
	constant cc;
	cc.m_time = ::GetTickCount64();

	m_deltaPosition += m_deltaTime / 10.0f;

	if (m_deltaPosition > 1.0f)
	{
		m_deltaPosition = 0;
	}

	Matrix4x4 temp;

	m_deltaScale += m_deltaTime / 1.10f;
	cc.m_world.SetScale(Vector3D(1, 1, 1));

	temp.SetIdentity();
	temp.SetRotationZ(0.0);
	cc.m_world *= temp;

	temp.SetIdentity();
	temp.SetRotationY(m_rotationY);
	cc.m_world *= temp;

	temp.SetIdentity();
	temp.SetRotationX(m_rotationX);
	cc.m_world *= temp;

	//cc.m_world.SetScale(Vector3D::Lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (float)(sin(m_delta_scale) + 1.0f) / 2.0f));
	//temp.SetTranslation(Vector3D::Lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), (float)m_deltaPosition));
	//cc.m_world *= temp;

	cc.m_view.SetIdentity();

	cc.m_proj.SetOrthoLH((this->GetClientWindowRect().right - this->GetClientWindowRect().left) / 400.0f, (this->GetClientWindowRect().bottom - this->GetClientWindowRect().top) / 400.0f, -4.0f, 4.0f);

	m_constantBuffer->Update(GraphicsEngine::Get()->GetImmediateDeviceContext(), &cc);
}


App::~App()
{
}

void App::OnCreate()
{
	Window::OnCreate();


	InputSystem::Get()->AddListener(this);


	GraphicsEngine::Get()->Initialize();
	m_swapChain = GraphicsEngine::Get()->CreateSwapChain();

	RECT rc = this->GetClientWindowRect();
	m_swapChain->Initialize(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	Vertex vertexList[] =
	{

		{Vector3D(-0.5f, -0.5f, -0.5f),    Vector3D(1, 0, 0),   Vector3D(0.2f, 0,     0) },
		{Vector3D(-0.5f,  0.5f, -0.5f),    Vector3D(1, 1, 0),   Vector3D(0.2f, 0.2f,  0) },
		{ Vector3D(0.5f,  0.5f, -0.5f),    Vector3D(1, 1, 0),   Vector3D(0.2f, 0.2f,  0) },
		{ Vector3D(0.5f, -0.5f, -0.5f),    Vector3D(1, 0, 0),   Vector3D(0.2f, 0,     0) },


		{ Vector3D(0.5f, -0.5f, 0.5f),     Vector3D(0, 1, 0),   Vector3D(0,   0.2f,    0) },
		{ Vector3D(0.5f,  0.5f, 0.5f),     Vector3D(0, 1, 1),   Vector3D(0,   0.2f, 0.2f) },
		{Vector3D(-0.5f,  0.5f, 0.5f),     Vector3D(0, 1, 1),   Vector3D(0,   0.2f, 0.2f) },
		{Vector3D(-0.5f, -0.5f, 0.5f),     Vector3D(0, 1, 0),   Vector3D(0,   0.2f,    0) }

	};

	m_vertexBuffer = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(vertexList);

	unsigned int indexList[] = {
		0,1,2,
		2,3,0,
		4,5,6,
		6,7,4,
		1,6,5,
		5,2,1,
		7,0,3,
		3,4,7,
		3,2,5,
		5,4,3,
		7,6,1,
		1,0,7
	};
	UINT size_indexList = ARRAYSIZE(indexList);


	m_indexBuffer = GraphicsEngine::Get()->CreateIndexBuffer();
	m_indexBuffer->Load(indexList, size_indexList);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::Get()->CompileVertexShader(L"Assets/Shaders/VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vertexShader = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vertexBuffer->Load(vertexList, sizeof(Vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::Get()->ReleaseCompiledShader();


	GraphicsEngine::Get()->CompilePixelShader(L"Assets/Shaders/PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_pixelShader = GraphicsEngine::Get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();

	constant cc;
	cc.m_time = 0;

	m_constantBuffer = GraphicsEngine::Get()->CreateConstantBuffer();
	m_constantBuffer->Load(&cc, sizeof(constant));

}

void App::OnUpdate()
{
	Window::OnUpdate();


	InputSystem::Get()->Update();


	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swapChain, 0, 0.0f, 0.0f, 1);

	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	UpdateQuadPosition();

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetConstantBuffer(m_vertexShader, m_constantBuffer);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetConstantBuffer(m_pixelShader, m_constantBuffer);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vertexShader);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetPixelShader(m_pixelShader);


	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vertexBuffer);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetIndexBuffer(m_indexBuffer);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_indexBuffer->GetSizeIndexList(), 0, 0);
	m_swapChain->Present(true);


	m_oldDelta = m_newDelta;
	m_newDelta = ::GetTickCount64();

	m_deltaTime = (m_oldDelta) ? ((m_newDelta - m_oldDelta) / 1000.0f) : 0;
}

void App::OnDestroy()
{
	Window::OnDestroy();

	m_vertexBuffer->Release();
	m_constantBuffer->Release();
	m_indexBuffer->Release();
	m_swapChain->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();

	GraphicsEngine::Get()->Release();
}

void App::OnKeyDown(int key)
{
	if (key == 'W' || key == 38)
	{
		m_rotationX += 2.75 * m_deltaTime;
	}
	else if(key == 'S' || key == 40)
	{
		m_rotationX -= 2.75 * m_deltaTime;
	}
	if (key == 'A' || key == 37)
	{
		m_rotationY += 2.75 * m_deltaTime;
	}
	else if (key == 'D' || key == 39)
	{
		m_rotationY -= 2.75 * m_deltaTime;
	}
}

void App::OnKeyUp(int key)
{
}
