#include "App.h" //includes all of the includes that have to be included.
SDL_Window* displayWindow;

int main(int argc, char *argv[])
{
    App app;
    while(!app.UpdateAndRender()){}
    return 0;
}