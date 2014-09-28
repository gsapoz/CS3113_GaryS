//
//  Entity.h
//  SpaceInvaders
//
//  Created by GaryS on 9/28/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#ifndef __SpaceInvaders__Entity__
#define __SpaceInvaders__Entity__
#include "Bullets.h"
#include<SDL2/SDL_opengl.h>

namespace SpaceInvaders {
    class Entity{
    public:
        void draw(float stretch = 1.0f);
        void render();
        
        GLuint textureID;
        
        float u;
        float v;
        float scale;
        
        float x;
        float y;
        
        float width;
        float height;
        
        float d_x;
        float d_y;
        
        float waittime;
        
        bool alive;
        bool shot;
        
        Bullet bullet;
        Entity(){};
        Entity(GLuint textureID, float u, float v, float width, float height, float scale)
		:textureID(textureID), u(u), v(v), width(width), height(height), scale(scale), alive(true), d_x(0.1f), d_y(0.04f), shot(false), waittime(-999.0f){};
    };
}


#endif /* defined(__SpaceInvaders__Entity__) */
