// Shooter_Raylib.cpp : Defines the entry point for the application.
//

#include "Shooter_Raylib.h"
#include "Tools/IniParser.h"
#include "Core/Window.h"

#include <string>

#include <iostream>

#include "Core/LevelSerializer.h"

int main()
{
	World* DefaultWorld = g_LevelSerializer.Load("DefaultLevel.json");
	if (!DefaultWorld)
	{
		return 10;
	}
	g_Window.CreateWindow();
	// Shutdown
	//delete _Window;
	//_Window = nullptr;

	return 0;
}
