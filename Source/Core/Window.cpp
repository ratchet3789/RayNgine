#include "Window.h"
#include "../Tools/IniParser.h"

#include <string>

Window::Window()
{
	int ResX = g_IniParser.GetOrDefault<int>("Graphics", "ResX", 1280);
	int ResY = g_IniParser.GetOrDefault<int>("Graphics", "ResY", 720);
	std::string Title = g_IniParser.GetOrDefault<std::string>("Graphics", "Title", "Window");

	InitWindow(ResX, ResY, Title.c_str());

	while (!WindowShouldClose())
	{
		Render();
	}
}

Window::~Window()
{
	CloseWindow();
}

void Window::Render()
{
	ClearBackground(Color(39, 58, 93, 255));
	BeginDrawing();
	// 3d models and shit
	int ResX, ResY;
	GetRendererScale(ResX, ResY);
	DrawCircle(ResX * 0.5f, ResY * 0.5f, 32.0f, Color(255, 255, 255, 255));
	EndDrawing();
}

void Window::GetRendererScale(int& ResX, int& ResY)
{
	ResX = GetRenderWidth();
	ResY = GetRenderHeight();
}
