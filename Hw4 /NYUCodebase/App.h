//
//  App.h
//  NYUCodebase
//
//  Created by GaryS on 10/4/14.
//  Copyright (c) 2014 Ivan Safrin. All rights reserved.
//
//  Where all the magic happens

#ifndef __NYUCodebase__App__
#define __NYUCodebase__App__

#include "SheetSprite.h" 
#include "Entity.h"
#include "Bullet.h"

#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<string>
#include<vector>

class App
{
    bool done;
    float lastFrameTicks;
    float timeLeftOver;
    SDL_Window* displayWindow;
    GLuint characterTexture;
    GLuint brickTexture;
    float gravity_x;
    float gravity_y;
    int bulletIndex;
    Bullet bullets[30];
    int brickIndex;
    Entity bricks[200];
    int enemyIndex;
    Entity enemies[8];
    Entity* player;
    std::vector<Entity*> entities;
    float shootTimer;
    float enemySpawnTimer;
public:
    App();
    ~App();
    void Init();
    void Update(float elapsed);
    //void FixedUpdate();
    void Render();
    bool UpdateAndRender();
    void buildLevel();
    void shootBullet();
};
//float lerp(float v0, float v1, float t);

#endif /* defined(__NYUCodebase__App__) */

