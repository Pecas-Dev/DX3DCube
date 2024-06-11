#pragma once
#include <DX3DCube/Input/InputListener.h>
#include <map>


class InputSystem
{
private:
	unsigned char m_keysState[256] = {};
	unsigned char m_oldKeysState[256] = {};


	std::map<InputListener*, InputListener*> m_mapListeners;

public:
	InputSystem();
	~InputSystem();

	void AddListener(InputListener* inputListener);
	void RemoveListener(InputListener* inputListener);

	void Update();

	static InputSystem* Get();
};

