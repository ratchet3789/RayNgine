#include "Circle2D.h"
#include <raylib.h>
#include "../../Window.h" // Todo: Intermediate classes so we don't just get the window res from the window itself
#include "../../../Debugging/Logger.h"

void Circle2D::Tick(float DeltaTime)
{
	if ((NodeTransform.Location.X - CircleRadius < 0.0f || NodeTransform.Location.X + CircleRadius > ScreenResolution.
	     X))
	{
		Velocity.X = -Velocity.X;
	}

	if ((NodeTransform.Location.Y - CircleRadius < 0.0f || NodeTransform.Location.Y + CircleRadius > ScreenResolution.
	     Y))
	{
		Velocity.Y = -Velocity.Y;
	}

	DrawCircle(NodeTransform.Location.X, NodeTransform.Location.Y, CircleRadius, CircleColor);

	NodeTransform.Location += Velocity * DeltaTime;
	CircleColor = Color((NodeTransform.Location.X / ScreenResolution.X) * 255.0f,
	                    (NodeTransform.Location.Y / ScreenResolution.Y) * 255.0f, 128.0f, 255.0f);
}

#include <iostream>

void Circle2D::BeginPlay()
{
	g_Window.GetRendererScale(ScreenResolution.X, ScreenResolution.Y);
	NodeTransform.Location = Vec3(ScreenResolution.X * .5f, ScreenResolution.Y * .5f, 0.0f);

	std::cout << (offsetof(Circle2D, Velocity)) << '\n';
	std::cout << this << '\n';
}
