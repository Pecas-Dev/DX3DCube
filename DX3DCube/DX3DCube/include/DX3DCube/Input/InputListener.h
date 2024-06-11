#pragma once

class InputListener
{
private:

public:

	InputListener()
	{
	}

	~InputListener()
	{
	}



	virtual void OnKeyDown(int key) = 0;
	virtual void OnKeyUp(int key) = 0;
};
