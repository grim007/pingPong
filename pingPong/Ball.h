#pragma once
#include <raylib.h>
class Ball
{
private:
	void resetBall();	
	void playMusic(int);
public:
	// x and y coordinate of the ball
	float xCoordinate_;
	float yCoordinate_;
	
	// speed of the ball in x and y direction
	float speedX_;
	float speedY_;

	// radius of the ball
	float radius_;
	
	// keep track of the score
	static int cpuScore_;
	static int playerScore_;

	// Necessary sfxs
	Sound gameOver_;
	Sound playerScoreMusic_;
	Sound ballBounce_;
	
	// Draw ball
	void Draw(); 
	Ball(float,float,float,float,float); // x y speedX speedY radius
	
	void updateBallSpeed();
	
	~Ball();
};

