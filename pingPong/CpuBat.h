#pragma once
#include "Bat.h"
// Parent Class of this class is Bat
class CpuBat : public Bat
{
public:
	CpuBat(float,float,float,float,float);
	void updateBatPosition(float);
};

