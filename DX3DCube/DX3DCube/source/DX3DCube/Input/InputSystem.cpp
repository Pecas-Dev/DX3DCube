#include <DX3DCube/Input/InputSystem.h>
#include <Windows.h>

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::AddListener(InputListener* inputListener)
{
	m_mapListeners.insert(std::make_pair<InputListener*, InputListener*>(std::forward<InputListener*>(inputListener), std::forward<InputListener*>(inputListener)));
}

void InputSystem::RemoveListener(InputListener* inputListener)
{
	std::map<InputListener*, InputListener*>::iterator iterator = m_mapListeners.find(inputListener);

	if (iterator != m_mapListeners.end())
	{
		m_mapListeners.erase(iterator);
	}
}

void InputSystem::Update()
{
	if (::GetKeyboardState(m_keysState))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			if (m_keysState[i] & 0x80)
			{
				std::map<InputListener*, InputListener*>::iterator iterator = m_mapListeners.begin();

				while (iterator != m_mapListeners.end())
				{
					iterator->second->OnKeyDown(i);

					++iterator;
				}
			}
			else
			{
				if (m_keysState[i] != m_oldKeysState[i])
				{
					std::map<InputListener*, InputListener*>::iterator iterator = m_mapListeners.begin();

					while (iterator != m_mapListeners.end())
					{
						iterator->second->OnKeyUp(i);

						++iterator;
					}
				}
			}
		}

		::memcpy(m_oldKeysState, m_keysState, sizeof(unsigned char) * 256);
	}
}

InputSystem* InputSystem::Get()
{
	static InputSystem inputSystem;

	return &inputSystem;
}
