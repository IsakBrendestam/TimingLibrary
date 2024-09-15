#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "Application.h"

#include "Library/Tween.h"

int main()
{

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Test", 
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          700,
                                          700,
                                          SDL_WINDOW_ALLOW_HIGHDPI);
                                        
    // Enable V-Sync
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    auto time1 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::high_resolution_clock::now();

    bool running = true;
    SDL_Event event;
    double deltaTime = 0;

    Application* app = new Application();
    app->Init();

    SDL_Thread* threadID = SDL_CreateThread( TweenManager::Update, "LazyThread", nullptr);

    while (running)
    {
        time2 = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<double, std::milli>(time2 - time1).count() / 1000;

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

            app->Event(event);
        }       

        app->Update(deltaTime);


        SDL_RenderClear(renderer);
        app->Draw(renderer);
        SDL_SetRenderDrawColor(renderer, 218, 215, 205, 0);
        SDL_RenderPresent(renderer);

        time1 = time2;
    }

    app->Exit();
    delete app;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}