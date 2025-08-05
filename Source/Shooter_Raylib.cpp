// Shooter_Raylib.cpp : Defines the entry point for the application.
//

#include "Shooter_Raylib.h"
#include "Tools/IniParser.h"
#include "Debugging/Logger.h"
#include "Core/Window.h"

#include <string>

int main()
{
	Window* _Window = new Window();

	// Shutdown
	delete _Window;
	_Window = nullptr;

	return 0;
}
