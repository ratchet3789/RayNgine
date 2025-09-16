#ifndef Window_H
#define Window_H

#if _WIN32
#pragma once
#endif

#include "raylib.h"

class Window
{
public:
	Window();
	~Window();

	void Render();

	// Window Helpers
	inline void GetRendererScale(int& ResX, int& ResY)
	{
		ResX = GetRenderWidth();
		ResY = GetRenderHeight();
	}
};

extern Window g_Window;
#endif //Window_H