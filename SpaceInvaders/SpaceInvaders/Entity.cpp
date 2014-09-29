//
//  Entity.cpp
//  SpaceInvaders
//
//  Created by GaryS on 9/27/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#include "Entity.h"

void Entity::Draw()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
        
    glMatrixMode(GL_MODELVIEW);
        
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
        
    GLfloat quad[] = { width * -0.5f, height * 0.5f, width * -0.5f, height * -0.5f, width * 0.5f, height * -0.5f, width * 0.5f, height * 0.5f };
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
        
    GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}
    
void Entity::DrawSpriteSheetSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
        
    glMatrixMode(GL_MODELVIEW);
        
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
        
    GLfloat quad[] = { width * -0.5f, height * 0.5f, width * -0.5f, height * -0.5f, width * 0.5f, height * -0.5f, width * 0.5f, height * 0.5f };
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
        
    float u = (float)(((int)index) % spriteCountX) / (float)spriteCountX;
    float v = (float)(((int)index) / spriteCountX) / (float)spriteCountY;
    float spriteWidth = 1.0 / (float)spriteCountX;
    float spriteHeight = 1.0 / (float)spriteCountY;
        
    GLfloat quadUVs[] = { u, v, u, v + spriteHeight, u + spriteWidth, v + spriteHeight, u + spriteWidth, v };
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
        
}
void Entity::setSize(float w, float h) {
    width = w;
    height = h;
}
void Entity::setPosition(float xTemp, float yTemp, float r) {
    x = xTemp;
    y = yTemp;
    rotation = r;
}
void Entity::setMovement(float s, float a) {
    speed = s;
    angle = a;
}

