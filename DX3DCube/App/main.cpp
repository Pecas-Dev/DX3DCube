#include <DX3DCube/App/App.h>
#include <iostream>


int main()
{
	try
	{
		App app;
		if (app.Initialize())
		{
			while (app.IsRunning())
			{
				app.Broadcast();
			}
		}
	}

	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}
