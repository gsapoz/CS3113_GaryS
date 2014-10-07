//
//  Bullet.cpp
//  NYUCodebase
//
//  Created by GaryS on 10/4/14.
//  Copyright (c) 2014 Ivan Safrin. All rights reserved.
//

#include "Bullet.h"

Bullet::Bullet()
{
    x = -2.0f;
    y = -2.0f;
    width = 0.05f;
    height = 0.05f;
    velocity_x = 3.0f;
}
void Bullet::Update(float elapsed)
{
    x += velocity_x * elapsed;
}
void Bullet::Render()
{
    if(visible)
        sprite.Draw(width, height, x, y);
}