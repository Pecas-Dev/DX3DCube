#pragma once
#include <Windows.h>


class Window
{
protected:
	HWND m_hwnd;
	bool m_isRun;

public:
	Window();
	~Window();

	bool Initialize();
	bool Broadcast();
	bool Release();
	bool IsRunning();

	RECT GetClientWindowRect();
	void SetHWND(HWND hwnd);


	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestroy();
};

