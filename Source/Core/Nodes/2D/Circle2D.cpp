//
// Created by addic on 2025/09/17.
//

#include "Circle2D.h"
#include <raylib.h>
#include "../../Window.h" // Todo: Intermediate classes so we don't just get the window res from the window itself

void Circle2D::Tick(float DeltaTime)
{
	// 3d models and shit
	int ResX, ResY;
	g_Window.GetRendererScale(ResX, ResY);
	DrawCircle(ResX * 0.5f, ResY * 0.5f, 32.0f, Color(255, 255, 255, 255));
}