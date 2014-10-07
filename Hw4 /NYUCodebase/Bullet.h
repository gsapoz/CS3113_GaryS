//
//  Bullet.h
//  NYUCodebase
//
//  Created by GaryS on 10/4/14.
//  Copyright (c) 2014 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__Bullet__
#define __NYUCodebase__Bullet__

#include <stdio.h>
#include "SheetSprite.h"

class Bullet
{
public:
    Bullet();
    void Update(float elapsed);
    void Render();
    
    float visible;
    void FixedUpdate();
    
    SheetSprite sprite;
    
    float x;
    float y;
    
    float width;
    float height;
    float velocity_x;
    float velocity_y;
};

#endif /* defined(__NYUCodebase__Bullet__) */
