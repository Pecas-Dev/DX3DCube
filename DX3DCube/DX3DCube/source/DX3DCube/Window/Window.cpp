#include <DX3DCube/Window/Window.h>

Window::Window()
{

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->SetHWND(hwnd);
		window->OnCreate();
		break;
	}

	case WM_DESTROY:
	{
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->OnDestroy();
		::PostQuitMessage(0);
		break;
	}


	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}


bool Window::Initialize()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"DX3DWindow";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
	{
		return false;
	}

	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"DX3DWindow", L"My 3D Cube", WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	if (!m_hwnd)
	{
		return false;
	}

	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_isRun = true;

	return true;
}

bool Window::Broadcast()
{
	MSG msg;

	this->OnUpdate();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);

	return true;
}


bool Window::Release()
{
	if (!::DestroyWindow(m_hwnd))
	{
		return false;
	}

	return true;
}

bool Window::IsRunning()
{
	return m_isRun;
}

RECT Window::GetClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::SetHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

void Window::OnDestroy()
{
	m_isRun = false;
}

Window::~Window()
{
}