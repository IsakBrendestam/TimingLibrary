#include "Application.h"

#include <iostream>

#include "Library/Tween.h"

void Application::Init()
{
    m_rect = {100, 100, 100, 100};
    m_color = {122, 122, 122, 0};
    m_vertMoveEnable = true;
    m_horiMoveEnable = true;
}

void Application::Exit()
{

}

void Application::Event(SDL_Event event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        {
            const FuncTypes funcType = Func_EaseInOutQuart;

            if ((event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_w) && m_vertMoveEnable)
            {
                Tween* t = Tween::Create(m_rect.y);

                float moveValue = 100;
                if (event.key.keysym.sym == SDLK_w)
                    moveValue = -100;

                t->AddTimeFrameFunc(1, moveValue, funcType);
                t->AddUpdateFunction([this] (float value) -> void {
                    this->m_rect.y = value;
                    this->m_vertMoveEnable = false;
                });

                t->AddPercentageFunction(1, [this] (float value) -> void {
                    this->m_vertMoveEnable = true;
                });
            }

            if ((event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) && m_horiMoveEnable)
            {
                Tween* t = Tween::Create(m_rect.x);

                float moveValue = 100;
                if (event.key.keysym.sym == SDLK_a)
                    moveValue = -100;

                t->AddTimeFrameFunc(1, moveValue, funcType);
                t->AddUpdateFunction([this] (float value) -> void {
                    this->m_rect.x = value;
                    this->m_horiMoveEnable = false;
                });

                t->AddPercentageFunction(1, [this] (float value) -> void {
                    this->m_horiMoveEnable = true;
                });
            }
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