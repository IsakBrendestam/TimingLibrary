#include "Application.h"

#include <iostream>

#include "Library/Tween.h"

void Application::Init()
{
    m_rect = {100, 100, 100, 100};
    m_color = {122, 122, 122, 0};
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
        if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_UP)
        {
            Tween* t = Tween::Create(m_rect.y);

            if (event.key.keysym.sym == SDLK_DOWN)
                t->AddTimeFrameFunc(1, 100, FuncTypes::Func_EaseInOutElastic);
            if (event.key.keysym.sym == SDLK_UP)
                t->AddTimeFrameFunc(1, -100, FuncTypes::Func_EaseInOutElastic);

            t->AddUpdateFunction([this] (float value) -> void {
                this->m_rect.y = value;
            });
        }

        if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
        {
            Tween* t = Tween::Create(m_rect.x);

            if (event.key.keysym.sym == SDLK_RIGHT)
                t->AddTimeFrameFunc(1, 100, FuncTypes::Func_EaseInOutElastic);
            else if (event.key.keysym.sym == SDLK_LEFT)
                t->AddTimeFrameFunc(1, -100, FuncTypes::Func_EaseInOutElastic);

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
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &m_rect);
}