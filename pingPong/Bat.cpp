#include "Bat.h"
#include <raylib.h>


Bat::Bat(float x, float y, float speed, float width, float height)
{
	xCoordinate_ = x;
	yCoordinate_ = y;
	speedY_ = speed;
	width_ = width;
	height_ = height;
}

void Bat::Draw()
{
	//DrawRectangle(xCoordinate_, yCoordinate_, width_, height_, WHITE);
	DrawRectangleRounded(Rectangle{ xCoordinate_,yCoordinate_,width_,height_ }, 1, 4, RAYWHITE);
}

void Bat::updateBatPosition()
{
	if (IsKeyDown(KEY_UP))
	{
		if(yCoordinate_>=0)
			yCoordinate_ -= speedY_;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		if (yCoordinate_+height_ <= GetScreenHeight())
			yCoordinate_ += speedY_;
	}

	
}