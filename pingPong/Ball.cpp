#include "Ball.h"
#include <raylib.h>

void Ball::Draw()
{
	DrawCircle(xCoordinate_, yCoordinate_, radius_, WHITE);
}

// Constructor
Ball::Ball(float x,float y,float speedX,float speedY,float radius)
{
	xCoordinate_ = x;
	yCoordinate_ = y;
	speedX_ = speedX;
	speedY_ = speedY;
	radius_ = radius;
	gameOver_ = LoadSound("media\\gameOver.mp3");
	playerScoreMusic_= LoadSound("media\\playerScore.mp3");
	ballBounce_= LoadSound("media\\ballBounce.mp3");
	

}

void Ball::updateBallSpeed()
{
	xCoordinate_ += speedX_;
	yCoordinate_ += speedY_;

	// --- Bouncing of the ball
	if (yCoordinate_ + radius_ >= GetScreenHeight() || yCoordinate_-radius_<=0)
	{
		speedY_ *= -1;
		PlaySound(ballBounce_);
	}

	if (xCoordinate_ + radius_ >= GetScreenWidth() || xCoordinate_ - radius_ <= 0)
	{
		speedX_ *= -1;
		PlaySound(ballBounce_);
	}
	// ---

	// -- Score calculation
	if (xCoordinate_ + radius_ >= GetScreenWidth())
	{
		cpuScore_++;	
		playMusic(-1);
		resetBall();
	}

	if (xCoordinate_ - radius_ <= 0)
	{
		playerScore_++;
		playMusic(1);
		resetBall();
	}
	// --
}

// resets the position of the ball after either cpu or player scores a point
void Ball::resetBall()
{
	xCoordinate_ = GetScreenWidth() / 2;
	yCoordinate_ = GetScreenHeight() / 2;
	int speedChoices[2] = { -1,1 };
	speedX_ *= speedChoices[GetRandomValue(0, 1)];
	speedY_ *= speedChoices[GetRandomValue(0, 1)];
}

void Ball::playMusic(int music)
{
	switch (music)
	{
	case -1:
		PlaySound(gameOver_);
		break;
	case 1:
		PlaySound(playerScoreMusic_);
		break;
	}

}

// This resets the scores of the player and the cpu
void Ball::resetTheGame()
{
	playerScore_ = 0;
	cpuScore_ = 0;
}

// This destructor unloads the music
Ball::~Ball()
{
	UnloadSound(gameOver_);
	UnloadSound(playerScoreMusic_);
	UnloadSound(ballBounce_);
}
