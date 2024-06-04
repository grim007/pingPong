#include "CpuBat.h"
#include <raylib.h>

// Calls the parameterised constructor of the parent class
CpuBat::CpuBat(float x, float y, float speed,float width,float height) :Bat(x, y, speed,width,height)
{
	;
}

// Update the position of the bat based on the coordinate of the ping pong ball
void CpuBat::updateBatPosition(float ballY)
{
	// If the middle of the bat is lower than that of the ball then the bat moves up
	if (yCoordinate_ + height_/2 > ballY)
	{
		if (yCoordinate_ != 0)
			yCoordinate_ -=speedY_;
	}

	if (yCoordinate_ + height_ / 2 <=ballY)
	{
		if (yCoordinate_ + height_ != GetScreenHeight())
			yCoordinate_+=speedY_;
	}
}
