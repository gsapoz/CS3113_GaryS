//
//  Entity.cpp
//  NYUCodebase
//
//  Created by GaryS on 10/4/14.
//  Copyright (c) 2014 Ivan Safrin. All rights reserved.
//

#include "Entity.h"

Entity::Entity() {
    x = 0.0f;
    y = 0.0f;
    width = 0.2f;
    height = 0.2f;
    
    velocity_x = 0.0f;
    velocity_y = 0.0f;
    acceleration_x = 0.0f;
    acceleration_y = 0.0f;
    friction_x = 0.0f;
    friction_y = 0.0f;
    mass = 0.0f;
    isStatic = false;
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;

}

void Entity::Update(float elapsed){}

void Entity::Render()
{
    sprite.Draw(width, height, x, y);
}

void Entity::Jump()
{
    collidedBottom = false;
    jumped = true;
    velocity_y = 3.5f;
}
void Entity::WalkRight()
{
    turnLeft = false;
    if(velocity_x < 0.0f)
        velocity_x = 0.0f;
    if(velocity_x < 2.0f)
        acceleration_x = 9.0f;
}
void Entity::WalkLeft()
{
    turnLeft = true;
    if(velocity_x > 0.0f)
        velocity_x = 0.0f;
    if(velocity_x > -2.0f)
        acceleration_x = -9.0f;
}
void Entity::Stop()
{
    velocity_x = 0.0f;
    acceleration_x =0.0f;
}
bool Entity::collidesWith(Entity* entity) {
    float e1_y_max = y + height / 2;
    float e1_y_min = y - height / 2;
    float e1_x_max = x + width / 2;
    float e1_x_min = x - width / 2;
    
    float e2_y_max = entity->y + entity->height / 2;
    float e2_y_min = entity->y - entity->height / 2;
    float e2_x_max = entity->x + entity->width / 2;
    float e2_x_min = entity->x - entity->width / 2;
    
    if (e1_y_min > e2_y_max)
        return false;
    if (e1_y_max < e2_y_min)
        return false;
    if (e1_x_min > e2_x_max)
        return false;
    if (e1_x_max < e2_x_min)
        return false;
    
    return true;
}