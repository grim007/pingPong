#include "CpuBat.h"
#include <raylib.h>

CpuBat::CpuBat(float x, float y, float speed,float width,float height) :Bat(x, y, speed,width,height)
{
	;
}

void CpuBat::updateBatPosition(float ballY)
{
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
