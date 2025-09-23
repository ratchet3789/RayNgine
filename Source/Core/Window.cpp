#include "Window.h"
#include "../Tools/IniParser.h"

#include "World.h"
#include <string>

Window::Window()
{
}

Window::~Window()
{
	CloseWindow();
}

void Window::CreateWindow()
{
	int ResX = g_IniParser.GetOrDefault<int>("Graphics", "ResX", 1280);
	int ResY = g_IniParser.GetOrDefault<int>("Graphics", "ResY", 720);
	std::string Title = g_IniParser.GetOrDefault<std::string>("Graphics", "Title", "My Sick Ass Game Engine Because I'm Very Cool");

	InitWindow(ResX, ResY, Title.c_str());

	while (!WindowShouldClose())
	{
		Render();
	}
}

void Window::Render()
{
	ClearBackground(Color(39, 58, 93, 255));
	BeginDrawing();

	g_pWorld->Tick();

	EndDrawing();
}

Window g_Window;