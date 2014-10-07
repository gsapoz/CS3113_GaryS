//
//  Game.h
//  SpaceInvaders
//
//  Created by GaryS on 9/27/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#ifndef __SpaceInvaders__Game__
#define __SpaceInvaders__Game__

#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2/SDL_opengl.h>

#include<vector>
#include "SheetSprite.h"
#include "DrawText.h"

class ClassDemoApp
{
    SheetSprite p1;
	SheetSprite alien;
	std::vector<SheetSprite> Bullets;
	std::vector<SheetSprite> AlienBullets;
	std::vector<SheetSprite> Aliens;
    int nBullets;
	int nEnemyBullets;
	int lastShot;
    int score;
	DrawText WriteScore;
	int gameState;
	bool done;
	float lastFrameTicks;
    SDL_Window* displayWindow;
public:
	ClassDemoApp();
	~ClassDemoApp();
	GLuint LoadTexture(const char *image_path);
	void Init();
	bool UpdateAndRender();
	void YouShoot();
	void AlienShoots();
	void Render();
	void Update(float elapsed);
};

#endif /* defined(__SpaceInvaders__Game__) */
