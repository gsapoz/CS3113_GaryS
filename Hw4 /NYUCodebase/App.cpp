//
//  App.cpp
//  NYUCodebase
//
//  Created by GaryS on 10/6/14.
//  Copyright (c) 2014 Ivan Safrin. All rights reserved.
//


#include "App.h"

App::App()
{
    Init();
    lastFrameTicks = 0.0f;
    timeLeftOver = 0.0f;
    
    gravity_x = 0.0f;
    gravity_y = -9.8f;
    
    bulletIndex = 0;
    shootTimer = 0.1f;
    
    buildLevel();
    
    characterTexture = LoadTexture("george_0.png");
    
    SheetSprite playerSprite = SheetSprite(characterTexture, 12, 8, 15);
    Entity player;
    player.sprite = playerSprite;
    player.y = -0.5f;
    player.width = 0.2f;
    player.height = 0.2f;
    player.friction_x = 3.0f;
    entities.push_back(&player);
    
}

App::~App()
{
    SDL_Quit();
}

void App::Init()
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Gary's Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
}

void App::Update(float elapsed)
{
    if (enemySpawnTimer > 1.0f && enemyIndex < 8) {
        SheetSprite enemySprite = SheetSprite(characterTexture, 12, 8, 2);
        enemies[enemyIndex].sprite = enemySprite;
        enemies[enemyIndex].y = 0.85f;
        enemies[enemyIndex].x = 0.65f;
        enemies[enemyIndex].width = 0.2f;
        enemies[enemyIndex].height = 0.2f;
        enemies[enemyIndex].acceleration_x = -2.0f;
        entities.push_back(&enemies[enemyIndex]);
        enemyIndex++;
        enemySpawnTimer = 0.0f;
    }
    
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i]->Update(elapsed);
    }
    
    for (size_t i = 0; i < 30; i++) {
        bullets[i].Update(elapsed);
    }
    
    shootTimer += elapsed;
    enemySpawnTimer += elapsed;
}

void App::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i]->Render();
    }
    
    for (size_t i = 0; i < 30; i++) {
        bullets[i].Render();
    }
    SDL_GL_SwapWindow(displayWindow);
}

bool App::UpdateAndRender()
{
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                if (shootTimer > 0.1f)
                    shootBullet();
            }
        }
    }
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W]) {
        if (!player->jumped) {
            player->Jump();
        }
        
    }
    if (keys[SDL_SCANCODE_D]) {
        SheetSprite playerSprite = SheetSprite(characterTexture, 12, 8, 27);
        player->sprite = playerSprite;
        player->WalkRight();
    }
    else if (keys[SDL_SCANCODE_A]) {
        SheetSprite playerSprite = SheetSprite(characterTexture, 12, 8, 15);
        player->sprite = playerSprite;
        player->WalkLeft();
    }
    else {
        player->Stop();
    }
    if (keys[SDL_SCANCODE_X]) {
        if (shootTimer > 0.1f) {
            shootTimer = 0.0f;
            shootBullet();
        }
    }
    Update(elapsed);
    Render();
    return done;
}
void App::buildLevel()
{   //A level is made of bricks, generated from a spritesheet.
    brickIndex = 0;
    brickTexture = LoadTexture("sheet_4.png");
    SheetSprite brickSprite;
    for (float i = -1.0f; i <= 1.0f; i = i + 0.2f) {
        brickSprite = SheetSprite(brickTexture, 14, 8, 7 + rand() % 3);
        bricks[brickIndex].sprite = brickSprite;
        bricks[brickIndex].isStatic = true;
        bricks[brickIndex].y = -0.9f;
        bricks[brickIndex].x = i;
        bricks[brickIndex].width = 0.2f;
        bricks[brickIndex].height = 0.2f;
        entities.push_back(&bricks[brickIndex]);
        brickIndex++;
    }
    brickSprite = SheetSprite(brickTexture, 14, 8, 27);
    for (float i = -0.4f; i <= 1.0f; i = i + 0.2f) {
        bricks[brickIndex].sprite = brickSprite;
        bricks[brickIndex].isStatic = true;
        bricks[brickIndex].y = i;
        bricks[brickIndex].x = -1.23f;
        bricks[brickIndex].width = 0.2f;
        bricks[brickIndex].height = 0.2f;
        entities.push_back(&bricks[brickIndex]);
        brickIndex++;
    }
    for (float i = -0.4f; i <= 1.0f; i = i + 0.2f) {
        bricks[brickIndex].sprite = brickSprite;
        bricks[brickIndex].isStatic = true;
        bricks[brickIndex].y = i;
        bricks[brickIndex].x = 1.23f;
        bricks[brickIndex].width = 0.2f;
        bricks[brickIndex].height = 0.2f;
        entities.push_back(&bricks[brickIndex]);
        brickIndex++;
    }
    
    for (float i = -0.4f; i <= 0.4f; i = i + 0.2f) {
        brickSprite = SheetSprite(brickTexture, 14, 8, 11);
        bricks[brickIndex].sprite = brickSprite;
        bricks[brickIndex].isStatic = true;
        bricks[brickIndex].y = 0.1f;
        bricks[brickIndex].x = i;
        bricks[brickIndex].width = 0.2f;
        bricks[brickIndex].height = 0.2f;
        entities.push_back(&bricks[brickIndex]);
        brickIndex++;
    }
    
    for (float i = -1.05f; i <= -0.8f; i = i + 0.2f) {
        brickSprite = SheetSprite(brickTexture, 14, 8, 11);
        bricks[brickIndex].sprite = brickSprite;
        bricks[brickIndex].isStatic = true;
        bricks[brickIndex].y = -0.4f;
        bricks[brickIndex].x = i;
        bricks[brickIndex].width = 0.2f;
        bricks[brickIndex].height = 0.2f;
        entities.push_back(&bricks[brickIndex]);
        brickIndex++;
    }
    
    for (float i = 1.05f; i >= 0.8f; i = i - 0.2f) {
        brickSprite = SheetSprite(brickTexture, 14, 8, 11);
        bricks[brickIndex].sprite = brickSprite;
        bricks[brickIndex].isStatic = true;
        bricks[brickIndex].y = -0.4f;
        bricks[brickIndex].x = i;
        bricks[brickIndex].width = 0.3f;
        bricks[brickIndex].height = 0.2f;
        entities.push_back(&bricks[brickIndex]);
        brickIndex++;
    }
}
void App::shootBullet()
{
    SheetSprite bulletSprite = SheetSprite(characterTexture, 12, 8, 3);
    bullets[bulletIndex].sprite = bulletSprite;
    bullets[bulletIndex].visible = true;
    bullets[bulletIndex].x = player->x;
    bullets[bulletIndex].y = player->y;
    if (player->turnLeft)
        bullets[bulletIndex].velocity_x = -3.5f;
    else
        bullets[bulletIndex].velocity_x = 3.5f;
    bulletIndex++;
    if (bulletIndex > 30 - 1) {
        bulletIndex = 0;
    }
    shootTimer = 0;
}











