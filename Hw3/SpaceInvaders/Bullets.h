//
//  Bullets.h
//  SpaceInvaders
//
//  Created by GaryS on 9/28/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#ifndef __SpaceInvaders__Bullets__
#define __SpaceInvaders__Bullets__

#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2/SDL_opengl.h>

namespace SpaceInvaders
{
    struct Bullet
    {
    public:
        void draw();
        void update();
        float u;
        float v;
        float width;
        float height;
        float scale;
        
        float x;
        float y;
        float speed;
        
        GLuint textureID;
        
        bool visible;
        float timeAlive;
        
        Bullet(){};
        Bullet(GLuint textureID, float u, float v, float width, float height, float scale, float x, float y, bool visible)
		:textureID(textureID), u(u), v(v), width(width), height(height), scale(scale), x(x), y(y), speed(0.4f), visible(visible){};
    };
}

#endif /* defined(__SpaceInvaders__Bullets__) */
