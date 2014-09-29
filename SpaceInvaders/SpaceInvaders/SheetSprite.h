//
//  SheetSprite.h
//  SpaceInvaders
//
//  Created by GaryS on 9/27/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#ifndef __SpaceInvaders__SheetSprite__
#define __SpaceInvaders__SheetSprite__

#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2/SDL_opengl.h>

class SheetSprite {
public:
	SheetSprite() {
		timeAlive = 0.0;
	}
	SheetSprite(unsigned int textureID, float u, float v, float width, float height, float scale, bool isVisible) { }
    
	void setAttributes(unsigned int t, float u_, float v_, float w, float h, float s, bool vis, float x_, float y_);
	void Draw();
	void setPosition(float xTemp, float yTemp);
    
	float scale;
	unsigned int textureID;
	float u;
	float v;
	float width;
	float height;
    
	float x;
	float y;
	float direction;
    
	float timeAlive;
	bool isVisible;
};

#endif /* defined(__SpaceInvaders__SheetSprite__) */
