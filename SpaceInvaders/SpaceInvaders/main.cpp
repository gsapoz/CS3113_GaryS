//
//  main.cpp
//  SpaceInvaders
//
//  Created by GaryS on 9/28/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2/SDL_opengl.h>
#include "Entity.h"
#include "Bullets.h"
using namespace SpaceInvaders;

SDL_Window* displayWindow;

enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL, STATE_GAME_OVER };
int main(int argc, const char * argv[])
{

    // insert code here...
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
    
	bool done = false;
	
	SDL_Event event;
    
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
		}
		SDL_GL_SwapWindow(displayWindow);
	}
    
	SDL_Quit();
	return 0;
}

//Users/MikeS/Workspace/cs3113/project_template/Xcode/NYUCodebase/main.cpp