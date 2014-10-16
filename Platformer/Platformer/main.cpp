//
//  main.cpp
//  Platformer
//
//  Created by GaryS on 10/16/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//
#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2/SDL_opengl.h>

int main(int argc, const char * argv[]){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        puts("SDL_Init error");
        return -1;
    } else {
        puts("SDL_Init success!");
        return 0;
    }
}