#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Entity.h" //Framework for Entity class. 
#include<math.h>
using namespace Entities;

SDL_Window* displayWindow;

//score won't be shown, but will be detected
bool I_Scored = true; //Player 1 scored. Else, player 2 scored! 
int myScore = 0; 
int aiScore = 0; 

Entity myPaddle; //player 1 paddle
Entity aiPaddle; //player 2 paddle
Entity ball;  //pong ball

GLuint LoadTexture(const char* image_path, GLenum image_format = GL_BGRA) {
    //Function Acquired in Lecture Notes
	SDL_Surface *surface = IMG_Load(image_path);
    
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
    
	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, image_format, GL_UNSIGNED_BYTE, surface->pixels);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    SDL_FreeSurface(surface);
    
	return textureID;
}

void Setup() {
	//Function Acquired in Lecture Notes
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Pong!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);

	SDL_GL_MakeCurrent(displayWindow, context);
    
	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
}

bool ProcessEvents() {
	//Function Acquired in Lecture Notes
	SDL_Event event;
    
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			return false;
		}
	}

	//key-input (A/Z controls player 1 paddle, Up/Down controls AI paddle.  
	const Uint8* cmd = SDL_GetKeyboardState(NULL);

	if(cmd[SDL_SCANCODE_A] == 1) myPaddle.dir_y = 1.0f; 
	else if(cmd[SDL_SCANCODE_Z]) myPaddle.dir_y = -1.0f; 

	if(cmd[SDL_SCANCODE_UP] == 1) aiPaddle.dir_y = 1.0f; 
	else if(cmd[SDL_SCANCODE_DOWN]) aiPaddle.dir_y = -1.0f; 

	//Winner gets ball! 
	if(ball.x == 0.0f && ball.y == 0.0f && ball.dir_x == 0.0f && ball.dir_y == 0.0f)
	{
		if(I_Scored) ball.dir_x = 1.0f;
		else ball.dir_x = -1.0f;
	} 

	//ball dimensions
	float ballRight = ball.x + ball.width / 2;
	float ballLeft = -(ball.x + ball.width / 2);
	float ballTop = ball.y + ball.height /2;
	float ballBottom = -(ball.y + ball.height/2);
	//player 1 paddle dimensions
	float myPaddleRight = myPaddle.x + myPaddle.width / 2;
	float myPaddleLeft = -(myPaddle.x + myPaddle.width / 2);
	float myPaddleTop = myPaddle.y + myPaddle.height /2;
	float myPaddleBottom = -(myPaddle.y + myPaddle.height/2);
	//player 2 paddle dimensions
	float aiPaddleRight = aiPaddle.x + aiPaddle.width / 2;
	float aiPaddleLeft = -(aiPaddle.x + aiPaddle.width /2);
	float aiPaddleTop = aiPaddle.y + aiPaddle.height /2;
	float aiPaddleBottom = -(aiPaddle.y + aiPaddle.height /2);

	//Detect Collisions
	if((ballTop >= 1.0f) || (ballBottom <= -1.0f))
	{   //ball made contact with ceiling/floor
		ball.dir_y *= -1.0f; //richocet! 
	}
	if((ballLeft <= myPaddleRight) && (ballTop >= myPaddleBottom) && (ballBottom <= myPaddleTop))
	{   //ball made contact with player 1's paddle
		ball.dir_x *= -1; //knock away
		ball.dir_y = myPaddle.dir_y * myPaddle.speed;
	} 
	if((ballRight >= aiPaddleRight) && (ballTop >= aiPaddleBottom) && (ballBottom <= aiPaddleTop))
	{   //ball made contact with player 2's paddle
		ball.dir_x *= -1; //knock away
		ball.dir_y = aiPaddle.dir_y * aiPaddle.speed;
	} 
    
	return true;
}

void Update(float elapsed) {
	//function from lecture notes
	myPaddle.y += myPaddle.dir_y * elapsed;
	aiPaddle.y += aiPaddle.dir_y * elapsed;

	//fabs() is the absolute value operator, from math.h
	myPaddle.speed += (float)(fabs(myPaddle.dir_y * elapsed)/1000 + 0.0001);
	aiPaddle.speed += (float)(fabs(aiPaddle.dir_y * elapsed)/1000 + 0.0001);

	//Screen Restraints
	if(myPaddle.y > 0.825f)
		myPaddle.y = 0.825f;
	if(myPaddle.y < -0.825f)
		myPaddle.y = -0.825f;
	myPaddle.dir_y = 0; //stops further movement!
	//Paddle 2
	if(aiPaddle.y > 0.825f)
		aiPaddle.y = 0.825f;
	if(aiPaddle.y < -0.825f)
		aiPaddle.y = -0.825f;
	aiPaddle.dir_y = 0; //stops further movement!
}

void Render() {
	//function from class lecture 
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.4f, 0.5f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//render entities
	ball.Draw();
	myPaddle.Draw();
	aiPaddle.Draw();
	
	if(ball.x > 1.33)
	{ 
		++myScore;
		ball.x = 0.0f;
		ball.y = 0.0f;
		ball.dir_x = 0.0f;
		ball.dir_y = 0.0f;
		I_Scored = true;
	}
	else if(ball.x < -1.33)
	{
		++aiScore;
		ball.x = 0.0f;
		ball.y = 0.0f;
		ball.dir_x = 0.0f;
		ball.dir_y = 0.0f;
		I_Scored = false;
	}
		
	SDL_GL_SwapWindow(displayWindow);
}

//void Cleanup();
int main(int argc, char *argv[])
{
	Setup();
    
	float lastFrameTicks = 0.0f;
    
    //ball/paddle.textureID / x / y ...
	ball.textureID = LoadTexture("ballBlu.png");
	myPaddle.textureID = LoadTexture("paddleBlu.png");
	aiPaddle.textureID = LoadTexture("paddleRed.png");

	ball.SetSize(0.1f, 0.1f);
	myPaddle.SetSize(0.1f, 0.35f);
	aiPaddle.SetSize(0.1f, 0.35f);

	myPaddle.x = -1.0;
	aiPaddle.x = 1.0;

	//ProcessEvents();
	while (ProcessEvents()) {
		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		Update(elapsed);
		Render(); 
	}

	SDL_Quit();
	return 0;
}

/*
Author: Gary Sapozhnikov
Date: 09/21/2014

Sprites acquired from 
https://github.com/ivansafrin/CS3113/tree/master/assets/graphics/Puzzle%20assets%20(80%20assets)/PNG
*/