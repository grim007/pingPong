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
	DrawRectangleRounded(Rectangle{ xCoordinate_,yCoordinate_,width_,height_ }, 1, 4, RAYWHITE);
}

// Update the position of the bat depending upon the buttons pressed
void Bat::updateBatPosition()
{
	if (IsKeyDown(KEY_UP))
	{
		if(yCoordinate_>=0) // This ensures bound control for the bats
			yCoordinate_ -= speedY_;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		if (yCoordinate_+height_ <= GetScreenHeight())
			yCoordinate_ += speedY_;
	}
}