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

class ClassDemoApp {
public:
    
	ClassDemoApp();
	~ClassDemoApp();
    
	GLuint LoadTexture(const char *image_path);
	void Init();
	bool UpdateAndRender();
    
	void shootLaser();
	void shootEnemyLaser();
    
	void Render();
	void Update(float elapsed);
    
private:
	SheetSprite ship;
	SheetSprite enemy1;
	std::vector<SheetSprite> lasers;
	std::vector<SheetSprite> enemyLasers;
	std::vector<SheetSprite> enemies;
    
	int numLasers;
	int numEnemyLasers;
	int lastShot;
	int score;
	DrawText writeScore;
    
	int gameState;
	bool done;
	float lastFrameTicks;
	SDL_Window* displayWindow;
};

#endif /* defined(__SpaceInvaders__Game__) */
