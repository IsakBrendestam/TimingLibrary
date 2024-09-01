#include "Application.h"

#include <iostream>

#include "Library/Tween.h"

void Application::Init()
{
    m_rect = {100, 100, 100, 100};

}

void Application::Exit()
{

}

void Application::Event(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        // Quitting if Esc is pressed
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            Tween* t = Tween::Create(100);
            t->AddTimeFrameValue(1, 500);
            t->AddUpdateFunction([this] (float value) -> void {
                this->m_rect.x = value;
            });
        }
        break;
    
    default:
        break;
    }
}

void Application::Update(double deltaTime)
{

}

void Application::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer, &m_rect);
}