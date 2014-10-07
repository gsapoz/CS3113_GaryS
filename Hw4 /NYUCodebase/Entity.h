//
//  Entity.h
//  NYUCodebase
//
//  Created by GaryS on 10/4/14.
//  Copyright (c) 2014 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__Entity__
#define __NYUCodebase__Entity__

#include "SheetSprite.h"
#include <stdio.h>

class Entity
{  
public:
    Entity();
    ~Entity();
    void Update(float elapsed);
    void Render();
    
    //movement
    void Jump();
    void WalkRight();
    void WalkLeft();
    void Stop();
    
    bool collidesWith(Entity *entity);
    
    SheetSprite sprite;
    float x;
    float y;
    
    float width;
    float height;
    float velocity_x;
    float velocity_y;
    float acceleration_x;
    float acceleration_y;
    float friction_x;
    float friction_y;
    float mass;
    bool isStatic;
    bool jumped;
    bool turnLeft;
    
    bool enableCollisions;
    
    bool collidedTop;
    bool collidedBottom; 
    bool collidedLeft; 
    bool collidedRight;
};

#endif /* defined(__NYUCodebase__Entity__) */
