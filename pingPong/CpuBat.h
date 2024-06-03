#pragma once
#include "Bat.h"
class CpuBat : public Bat
{
public:
	CpuBat(float,float,float,float,float);
	void updateBatPosition(float);
};

