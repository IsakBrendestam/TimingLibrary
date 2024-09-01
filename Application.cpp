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
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            int startY = m_rect.y;
            Tween* t = Tween::Create(100);
            t->AddTimeFrameFunc(1, 500, FuncTypes::Func_EaseInOutElastic);
            t->AddTimeFrameFunc(1, 200, FuncTypes::Func_Linear);
            t->AddFrameFunction(0, [this] (float value) -> void {
                this->m_rect.x = value;

            });
            t->AddFrameFunction(1, [this, startY] (float value) -> void {
                this->m_rect.y = startY - 600 + value;
            });

            /*
            t->AddUpdateFunction([this] (float value) -> void {
                this->m_rect.x = value;
            });
            */
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