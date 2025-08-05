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
	__forceinline void GetRendererScale(int& ResX, int& ResY);

};

#endif //Window_H