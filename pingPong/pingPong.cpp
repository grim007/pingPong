// Essential libraries
#include <iostream>
#include <raylib.h>
#include <string>
#include "Ball.h"
#include "Bat.h"
#include "CpuBat.h"

// Parameters required for the game
const int WIDTH = 1280;
const int HEIGHT = 800;
const float CENTER_SCREEN_X = WIDTH / 2.0f;
const float CENTER_SCREEN_Y = HEIGHT / 2.0f;

const float BAT_WIDTH = 20.0f;
const float BAT_HEIGHT = 100.0f;
const float CENTER_BAT_X = BAT_WIDTH / 2.0f;
const float CENTER_BAT_Y = BAT_HEIGHT / 2.0f;
const float PLAYER_BAT_SPEED = 7.0f;
const int BALL_SPEED = 9;
const float CPU_BAT_SPEED = 8.0f;
const float BALL_RADIUS = 15.0f;

const float GAP_FROM_EDGE = 10.0f;

int Ball::cpuScore_ = 0; // static counter for the cpu score
int Ball::playerScore_ = 0; // static counter for the player score

bool winStatus = false;
typedef enum GameScreen {mainMenu=0,gameScreen,endScreen} GameScreen;


void checkForCollisionWithBat(Ball& ball, Bat& theBat, Sound& ballHitsBat);
void drawFieldAndScore(Ball& pingPongBall);
void drawBatAndBall(Ball& pingPongBall, Bat& playerBat, CpuBat& botBat);
void updateTheScreen(Ball& pingPongBall, Bat& playerBat, CpuBat& botBat);
void drawMainMenu(GameScreen& currentScreen);
void isButtonPressed(GameScreen& currentScreen);
void gameEndCondition(Ball& pingPongBall, GameScreen& currentScreen);
void endGameDisplay(GameScreen& currentScreen);


int main()
{
	GameScreen currentScreen = mainMenu;
	InitWindow(WIDTH, HEIGHT, "Ping Pong Game");  // Initialize the window with width x height
	InitAudioDevice();							 // Initialize the audio devices
	Image icon = LoadImage("media\\puck.png");   // Load an image from the path
	
	SetWindowIcon(icon);						// Set the icon of the window
	SetTargetFPS(60);							// The game is capped at 60 fps
	
	// Creating a ball class with essential methods and attributes
	Ball pingPongBall(CENTER_SCREEN_X, CENTER_SCREEN_Y, BALL_SPEED,BALL_SPEED, BALL_RADIUS);
	// Bat class 
	Bat playerBat(WIDTH - BAT_WIDTH, CENTER_SCREEN_Y - CENTER_BAT_Y, PLAYER_BAT_SPEED, BAT_WIDTH, BAT_HEIGHT);
	// Cpu bat inherits from Bat
	CpuBat botBat(0, CENTER_SCREEN_Y - CENTER_BAT_Y, CPU_BAT_SPEED, BAT_WIDTH, BAT_HEIGHT);
	Sound ballHitsBat = LoadSound("media\\ballHitsBat.mp3");
	Music backgroundMusic = LoadMusicStream("media\\backgroundMusic.mp3");
	
	// This is the main game loop
	while (!WindowShouldClose())
	{
		// Updating the Screen
		BeginDrawing();
		switch (currentScreen)
		{
		case mainMenu:
			// Play the music in the main menu and draw the main menu design
			PlayMusicStream(backgroundMusic);
			UpdateMusicStream(backgroundMusic);
			drawMainMenu(currentScreen);
			break;
		case gameScreen:
			StopMusicStream(backgroundMusic);
			// Updates the screen with necessary changes
			updateTheScreen(pingPongBall, playerBat, botBat);

			//Checking for collision
			checkForCollisionWithBat(pingPongBall, playerBat, ballHitsBat); // collision with the plaerBat
			checkForCollisionWithBat(pingPongBall, botBat, ballHitsBat);   // collision with the cpu bat
			// This function draws the field and the writes the score on the field
			drawFieldAndScore(pingPongBall);

			// This function draws the bats and ball on the field
			drawBatAndBall(pingPongBall, playerBat, botBat);

			// Check if the game should end or not
			gameEndCondition(pingPongBall, currentScreen);
			break;
		case endScreen:
			// End Screen
			endGameDisplay(currentScreen);
			break;
		default:
			break;
		}
		EndDrawing();
	}
	UnloadSound(ballHitsBat);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}

// This display the end game screen
void endGameDisplay(GameScreen& currentScreen)
{
	ClearBackground(SKYBLUE);
	if (winStatus == false)
	{
		DrawText("You Lost!", 475, 300, 50, WHITE);
		isButtonPressed(currentScreen);
	}
	else
	{
		DrawText("You Won!", 475, 300, 50, WHITE);
		isButtonPressed(currentScreen);
	}
}

// This checks if the game should end or not and resets the scores of the player and the cpu
void gameEndCondition(Ball& pingPongBall,GameScreen& currentScreen)
{
	if (pingPongBall.cpuScore_ == 10)
	{
		currentScreen = endScreen;
		pingPongBall.resetTheGame(); // This is the method of the class ball which resets the game
	}
	else if (pingPongBall.playerScore_ == 10)
	{
		currentScreen = endScreen;
		pingPongBall.resetTheGame();
		winStatus = true;
	}
}

// This draws the main menu screen
void drawMainMenu(GameScreen& currentScreen)
{
	ClearBackground(SKYBLUE);
	DrawText("Press Enter To Play The Game", 300, 300, 50, WHITE);
	DrawText("*First to 10 points wins the game", 300, 400, 30, WHITE);
	isButtonPressed(currentScreen);
}

// Checks if Enter key is pressed and does tasks accordingly
void isButtonPressed(GameScreen& currentScreen)
{
	// This function ensures that the user can play the game after one game
	// This links the end game screen to the main menu
	if (IsKeyPressed(KEY_ENTER))
	{
		switch (currentScreen)
		{
		case mainMenu:
			currentScreen = gameScreen;
			break;
		case endScreen:
			currentScreen = mainMenu;
			break;
		default:
			break;
		}
	}
}

// This function checks for the collision of the ball with the bats
void checkForCollisionWithBat(Ball& ball,Bat& theBat,Sound& ballHitsBat)
{
	if (CheckCollisionCircleRec(Vector2{ ball.xCoordinate_,ball.yCoordinate_ }, ball.radius_, Rectangle{ theBat.xCoordinate_,theBat.yCoordinate_,theBat.width_,theBat.height_ }))
	{
		// Push the ball in the opposite direction
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