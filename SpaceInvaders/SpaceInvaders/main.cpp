//
//  main.cpp
//  SpaceInvaders
//
//  Created by GaryS on 9/27/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#include "Entity.h" //Entity class
#include "ClassDemoApp.h" //Game App functions
#include "DrawText.h" //draws text on screen
#include "SheetSprite.h" //bind sprites to keys 
//using namespace SpaceInvaders; //omited..because i'm not sure if its necessary
using namespace std;

SDL_Window* displayWindow;

int main(int argc, const char * argv[])
{
    // insert code here...
	ClassDemoApp app;
    while(!app.UpdateAndRender()) {}
    SDL_Quit();
    return 0;
}
