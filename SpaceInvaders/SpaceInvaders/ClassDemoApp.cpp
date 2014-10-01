//
//  ClassDemoApp.cpp
//  SpaceInvaders
//
//  Created by GaryS on 9/27/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#include "ClassDemoApp.h" 

ClassDemoApp::ClassDemoApp() //constructor
{
	Init();
	score = 0;
	gameState = 0;
	done = false;
	lastShot = 5;
	nBullets = 9;
	nEnemyBullets = 23;
	lastFrameTicks = 0.0f;
}

GLuint ClassDemoApp::LoadTexture(const char *image_path)
{
	SDL_Surface *surface = IMG_Load(image_path);
    
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
    
	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	SDL_FreeSurface(surface);
	return textureID;
}

void ClassDemoApp::Init()
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
    
	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    
	GLuint spriteSheetTexture = LoadTexture("sheet.png");
    
	ship.setAttributes(spriteSheetTexture, 346.0f / 1024.0f, 75.0f / 1024.0f, 98.0f / 1024.0f, 75.0f / 1024.0f, 0.7f, true, 0.0f, -0.85f);
    
	float xOrigin = -1.2f;
	float yOrigin = 0.7f;
	int count = 0;
	for (int i = 0; i < 24; i++) {
		SheetSprite enemy;
		enemy.setAttributes(spriteSheetTexture, 425.0f / 1024.0f, 384.0f / 1024.0f, 93.0f / 1024.0f, 84.0f / 1024.0f, 0.7f, true, xOrigin, yOrigin);
		enemy.direction = 1;
		xOrigin += 0.25f;
		count++;
		if (count % 6 == 0) {
			xOrigin = -1.2;
			yOrigin -= 0.2;
		}
		Aliens.push_back(enemy);
	}
    
	for (int i = 0; i < 10; i++) {
		SheetSprite laser;
		laser.setAttributes(spriteSheetTexture, 858.0f / 1024.0f, 230.0f / 1024.0f, 9.0f / 1024.0f, 54.0f / 1024.0f, 1.0f, false, -2.0f, -2.0f);
		Bullets.push_back(laser);
	}
    
	for (int i = 0; i < 24; i++) {
		SheetSprite alienBullets;
		alienBullets.setAttributes(spriteSheetTexture, 809.0f / 1024.0f, 437.0f / 1024.0f, 19.0f / 1024.0f, 30.0f / 1024.0f, 1.0f, false, -2.0f, -2.0f);
		AlienBullets.push_back(alienBullets);
        AlienBullets.push_back(alienBullets);
	}
    
	WriteScore.font = LoadTexture("font1.png");
	WriteScore.size = 0.1;
	WriteScore.spacing = -0.055;
	WriteScore.r = 0.0;
	WriteScore.g = 1.0;
	WriteScore.b = 0.0;
	WriteScore.a = 1.0;
}

ClassDemoApp::~ClassDemoApp() //destructor
{
	SDL_Quit();
}

void ClassDemoApp::YouShoot()
{
	if (nBullets >= 9) {
		nBullets = 0;
	}
	Bullets[nBullets].isVisible = true;
	Bullets[nBullets].x = ship.x;
	Bullets[nBullets].y = ship.y + 0.1f;
	nBullets++;
}

void ClassDemoApp::AlienShoots()
{
	nEnemyBullets = rand() % 24;
	if (Aliens[nEnemyBullets].isVisible) {
		AlienBullets[nEnemyBullets].isVisible = true;
		AlienBullets[nEnemyBullets].x = Aliens[nEnemyBullets].x;
		AlienBullets[nEnemyBullets].y = Aliens[nEnemyBullets].y - 0.1f;
	}
	srand(static_cast<unsigned int>(time(NULL)));
}

void ClassDemoApp::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    
	glMatrixMode(GL_MODELVIEW);
    
	glLoadIdentity();
    
	if (gameState == 0) {
		WriteScore.Draw("Aliens are approaching!", -1.0, 0.5);
		WriteScore.Draw("Kill them all!", -1.0, 0.3);
		WriteScore.Draw("Press Enter to begin.", -1.0, -0.7);
	}
    
	if (gameState == 1) {
		
		ship.Draw();
        
		for (SheetSprite e : Aliens) {
			if (e.isVisible == true) {
				e.Draw();
			}
		}
        
		for (SheetSprite l : Bullets) {
			if (l.isVisible == true) {
				l.Draw();
			}
		}
        
		for (SheetSprite el : Bullets) {
			if (el.isVisible == true) {
				el.Draw();
			}
		}
		
		std::string scoreString = std::to_string(score);
		WriteScore.Draw(scoreString, -1.2, 0.9);
        
	}
    
	if (gameState == 2) {
		WriteScore.Draw("Congratulations! You Win!", -1.0f, 0.3f);
	}
    
	if (gameState == 3) {
		WriteScore.Draw("GAME OVER", -1.0f, 0.0f);
	}
    
	SDL_GL_SwapWindow(displayWindow);
}

bool isCollision(SheetSprite laser, SheetSprite vessel) //its a hit!
{
	if (laser.isVisible == true && vessel.isVisible == true) {
		if (((vessel.y - laser.y) < (vessel.height / 1.75 + laser.height / 1.75) && (vessel.y - vessel.height / 1.75) < (laser.y + laser.height / 1.75)
             && (vessel.y + vessel.height / 1.75) > (laser.y - laser.height / 1.75) && (vessel.x - laser.x) < (vessel.width / 1.75 + laser.width / 1.75)
             && (vessel.x - vessel.height / 1.75) < (laser.x + laser.width / 1.75)
             && (vessel.x + vessel.height / 1.75) > (laser.x - laser.width / 1.75))) {
            return true;
        }
		return false;
	} return false;
}

void ClassDemoApp::Update(float elapsed)
{
	SDL_Event event;
    
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
        
		if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
			if (lastShot >= 10) {
				YouShoot();
				lastShot = 0;
			}
		}
		lastShot++;
	}
    
	if (gameState == 0) {
		if (keys[SDL_SCANCODE_0]) {
			gameState = 1;
		}
	}
    
	if (gameState == 1) {
		if (keys[SDL_SCANCODE_LEFT]) {
			ship.x -= elapsed * 1.5;
		}
		if (keys[SDL_SCANCODE_RIGHT]) {
			ship.x += elapsed * 1.5;
		}
        
		for (SheetSprite &l : Bullets) {
			if (l.isVisible == true) {
				l.y += elapsed;
                
				//l.timeAlive += elapsed;
				if (l.y >= 1.0f) {
					l.isVisible = false;
				}
			}
		}
        
		for (SheetSprite &el : AlienBullets) {
			el.y -= elapsed;
            
            //el.timeAlive += elapsed;
            if (el.y <= -1.0f) {
                el.isVisible = false;
            }
			
		}
        
		bool hasEnemies = false;
		for (int i = 0; i < Aliens.size(); i++) {
			if (Aliens[i].isVisible) {
				hasEnemies = true;
				if (rand() % 2 == 1) {
					AlienShoots();
				}
			}
			srand(static_cast<unsigned int>(time(NULL)));
            
			Aliens[i].x += elapsed * 0.5 * Aliens[i].direction;
			if (((Aliens[i].x > 1.2) && (Aliens[i].isVisible)) || ((Aliens[i].x < -1.2) && (Aliens[i].isVisible)))
            {
				for (int j = 0; j < Aliens.size(); j++) {
					Aliens[j].x += .01 * -1 * Aliens[j].direction;
					Aliens[j].direction *= -1;
					Aliens[j].y -= 0.075f;
				}
			}
			for (int k = 0; k < Bullets.size(); k++) {
				if (isCollision(Bullets[k], Aliens[i])) {
                    Aliens[i].isVisible = false;
					Bullets[k].isVisible = false;
					score += 100;
				}
			}
			if (isCollision(Aliens[i], ship)) {
				gameState = 3;
			}
		}
		for (int i = 0; i < AlienBullets.size(); i++) {
			if (isCollision(ship, AlienBullets[i])){
				gameState = 3;
			}
		}
		if (!hasEnemies) {
			gameState = 2;
		}
	}
}

bool ClassDemoApp::UpdateAndRender()
{
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;
    
	Update(elapsed);
	Render();
	return done;
}