//
//  main.cpp
//  SpaceInvaders
//
//  Created by GaryS on 9/27/14.
//  Copyright (c) 2014 Gary. All rights reserved.
//

#include "Entity.h"
#include "ClassDemoApp.h"
#include "DrawText.h"
#include "SheetSprite.h"
//using namespace SpaceInvaders; //omited
using namespace std;

SDL_Window* displayWindow;

int main(int argc, const char * argv[])
{
    // insert code here...
	ClassDemoApp app;
    while(!app.UpdateAndRender()) {}
    return 0;
}
