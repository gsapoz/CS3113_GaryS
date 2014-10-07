//
//  SheetSprite.h
//  NYUCodebase
//
//  Created by GaryS on 10/4/14.
//  Copyright (c) 2014 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__SheetSprite__
#define __NYUCodebase__SheetSprite__

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_opengl.h>
#include <stdio.h>

class SheetSprite
{
public:
    SheetSprite();
    SheetSprite(GLuint textureID, unsigned int spriteCountX, unsigned int spritecountV, unsigned int index);
    
    void Draw(float width, float height, float x, float y);
    
    GLuint textureID;
    unsigned int countX;
    unsigned int countY;
    unsigned int index;
};
GLuint LoadTexture(const char* image_path);

#endif /* defined(__NYUCodebase__SheetSprite__) */
