//
//  DrawText.h
//  SpaceInvaders
//
//  Created by GaryS on 9/27/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#ifndef __SpaceInvaders__DrawText__
#define __SpaceInvaders__DrawText__

#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2/SDL_opengl.h>
#include <string>

class DrawText {
public:
	//void Draw(float x, float y);
	void Draw(std::string text, float x, float y);
    
	int font;
	//string text;
	float size;
	float spacing;
	float r;
	float g;
	float b;
	float a;
};

#endif /* defined(__SpaceInvaders__DrawText__) */
