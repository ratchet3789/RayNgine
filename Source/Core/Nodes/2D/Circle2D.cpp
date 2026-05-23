#include "Circle2D.h"
#include <raylib.h>
#include <iostream>
#include "../../Window.h" // Todo: Intermediate class so we don't just get the window res from the window itself

void Circle2D::Tick(float DeltaTime)
{
	if ((NodeTransform.Location.X - DvdTexture.width*0.38 < 0.0f || NodeTransform.Location.X + DvdTexture.width*0.38 > ScreenResolution.
	     X))
	{
		Velocity.X = -Velocity.X;
	}

	if ((NodeTransform.Location.Y - DvdTexture.height*0.28 < 0.0f || NodeTransform.Location.Y + DvdTexture.height*0.28 > ScreenResolution.
	     Y))
	{
		Velocity.Y = -Velocity.Y;
	}

	DrawTexture(DvdGlow, NodeTransform.Location.X - DvdTexture.width / 2, NodeTransform.Location.Y - DvdTexture.height / 2, CircleColor);
	DrawTexture(DvdTexture, NodeTransform.Location.X - DvdTexture.width / 2, NodeTransform.Location.Y - DvdTexture.height / 2, Color(255,255,255,255));
	//DrawCircle(NodeTransform.Location.X, NodeTransform.Location.Y, CircleRadius, CircleColor);

	NodeTransform.Location += Velocity * DeltaTime;
	CircleColor = Color{(uint8_t)((NodeTransform.Location.X / ScreenResolution.X) * 255),
	                    (uint8_t)((NodeTransform.Location.Y / ScreenResolution.Y) * 255), 128, 255};
}

void Circle2D::BeginPlay()
{
	g_Window.GetRendererScale(ScreenResolution.X, ScreenResolution.Y);
	NodeTransform.Location = Vec3(ScreenResolution.X * .5f, ScreenResolution.Y * .5f, 0.0f);
	DvdTexture = LoadTexture("Art/textures/DVDLogo_256.png");
	DvdGlow = LoadTexture("Art/textures/DVDLogoGlow_256.png");

	std::cout << (offsetof(Circle2D, Velocity)) << '\n';
	std::cout << this << '\n';
}
