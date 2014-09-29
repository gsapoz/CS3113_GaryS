//
//  Entity.h
//  SpaceInvaders
//
//  Created by GaryS on 9/27/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#ifndef __SpaceInvaders__Entity__
#define __SpaceInvaders__Entity__

#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2/SDL_opengl.h>


struct Entity {
    void Draw();
    void DrawSpriteSheetSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY);
    void setSize(float w, float h);
    void setPosition(float xTemp, float yTemp, float r);
    void setMovement(float s, float a);
        
    float x;
    float y;
    float rotation;
        
    int textureID;
        
    float width;
    float height;
    float speed;
    float angle;
};


#endif /* defined(__SpaceInvaders__Entity__) */
