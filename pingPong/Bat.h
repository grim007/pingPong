#pragma once
class Bat
{
public:
	float xCoordinate_;
	float yCoordinate_;
	float speedY_;
	float width_;
	float height_;

	void Draw();
	Bat(float,float,float,float,float);  // x y speedY width height
	void updateBatPosition();
	
};

