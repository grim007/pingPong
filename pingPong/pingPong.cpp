#include <iostream>
#include <raylib.h>
#include <string>
#include "Ball.h"
#include "Bat.h"
#include "CpuBat.h"

// Parameters required for the game
const int WIDTH = 1280;
const int HEIGHT = 800;
const float batWidth = 20.0f;
const float batHeight = 100.0f;
const float playerBatSpeed = 7.0f;
const int ballSpeed = 9;
float cpuBatSpeed = 8.0f;
float ballRadius = 15.0f;
int Ball::cpuScore_ = 0; // static counter for the cpu score
int Ball::playerScore_ = 0; // static counter for the player score

float gapFromTheEdge = 10.0f;
float centerOfScreenX = WIDTH / 2.0f;
float centerOfScreenY = HEIGHT / 2.0f;
float batCenterY = batHeight / 2.0f;
float batCenterX = batWidth / 2.0f;

void checkForCollisionWithBat(Ball& ball, Bat& theBat, Sound& ballHitsBat);
void drawFieldAndScore(Ball& pingPongBall);
void drawBatAndBall(Ball& pingPongBall, Bat& playerBat, CpuBat& botBat);
void updateTheScreen(Ball& pingPongBall, Bat& playerBat, CpuBat& botBat);

int main()
{
	
	InitWindow(WIDTH, HEIGHT, "Ping Pong Game");
	InitAudioDevice();
	Image icon = LoadImage("media\\puck.png");
	
	SetWindowIcon(icon);
	SetTargetFPS(60);
	Ball pingPongBall(centerOfScreenX, centerOfScreenY, ballSpeed,ballSpeed, ballRadius);
	Bat playerBat(WIDTH - batWidth, centerOfScreenY - batCenterY, playerBatSpeed, batWidth, batHeight);
	CpuBat botBat(0, centerOfScreenY - batCenterY, cpuBatSpeed, batWidth, batHeight);
	Sound ballHitsBat = LoadSound("media\\ballHitsBat.mp3");
	
	// This is the main game loop
	while (!WindowShouldClose())
	{
		// Updating the Screen
		BeginDrawing();
		
		// Updates the screen with necessary changes
		updateTheScreen(pingPongBall, playerBat, botBat);

		//Checking for collision
		checkForCollisionWithBat(pingPongBall, playerBat, ballHitsBat); // collision with the plaerBat
		checkForCollisionWithBat(pingPongBall, botBat, ballHitsBat);   // collision with the cpu bat

		// This function draws the field and the writes the score on the field
		drawFieldAndScore(pingPongBall);

		// This function draws the bats and ball on the field
		drawBatAndBall(pingPongBall, playerBat, botBat);

		EndDrawing();
	}
	UnloadSound(ballHitsBat);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}

void checkForCollisionWithBat(Ball& ball,Bat& theBat,Sound& ballHitsBat)
{
	if (CheckCollisionCircleRec(Vector2{ ball.xCoordinate_,ball.yCoordinate_ }, ball.radius_, Rectangle{ theBat.xCoordinate_,theBat.yCoordinate_,theBat.width_,theBat.height_ }))
	{
		ball.speedX_ *= -1;
		PlaySound(ballHitsBat);
	}

}

void drawFieldAndScore(Ball& pingPongBall)
{
	// Clearing screen before Drawing patterns
	ClearBackground(SKYBLUE);
	// Writing the score on the screen
	DrawText(TextFormat("%i", pingPongBall.cpuScore_), WIDTH / 2 - 30, 10, 30, WHITE);
	DrawText(TextFormat("%i", pingPongBall.playerScore_), WIDTH / 2 + 20, 10, 30, WHITE);

	// The central line at the screen
	DrawLine(WIDTH / 2, 0, WIDTH / 2, HEIGHT, WHITE);

	// Circular line in the middle of the screen
	DrawCircleLines(WIDTH / 2, HEIGHT / 2, 100, WHITE);
}

void drawBatAndBall(Ball& pingPongBall,Bat& playerBat,CpuBat& botBat)
{
	pingPongBall.Draw();
	playerBat.Draw();
	botBat.Draw();
}

void updateTheScreen(Ball& pingPongBall,Bat& playerBat,CpuBat& botBat)
{
	pingPongBall.updateBallSpeed(); // Update the position of ball 
	playerBat.updateBatPosition(); // update the position of bat
	botBat.updateBatPosition(pingPongBall.yCoordinate_);
}