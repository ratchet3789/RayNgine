#pragma once

#include "raylib.h"

class Window
{
public:
	Window();
	~Window();

	void CreateWindow();
	void Render();

	// Window Helpers
	inline void GetRendererScale(int& ResX, int& ResY)
	{
		ResX = GetRenderWidth();
		ResY = GetRenderHeight();
	}

	inline void GetRendererScale(float& ResX, float& ResY)
	{
		ResX = (float)GetRenderWidth();
		ResY = (float)GetRenderHeight();
	}
};

extern Window g_Window;