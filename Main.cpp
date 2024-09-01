#include <iostream>
#include <ctime>
#include <SDL2/SDL.h>

#include "Library/Tween.h"


int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Test", 
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          100,
                                          100,
                                          SDL_WINDOW_ALLOW_HIGHDPI);

    clock_t time1 = std::clock();
    clock_t time2 = std::clock();

    bool running = true;
    SDL_Event event;
    double deltaTime = 0;

    Tween tween(10);

    while (running)
    {
        time2 = std::clock();
        deltaTime = (double)(time2-time1)/CLOCKS_PER_SEC;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    // Quitting if Esc is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        running = false;
                    break;
            }
        }       

        time1 = time2;
        std::cout << tween.GetValue() << std::endl;
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}