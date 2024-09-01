#include "Application.h"

#include <iostream>

#include "Library/Tween.h"

void Application::Init()
{
    Tween* t = Tween::Create(10);
    t->AddUpdateFunction([] (float value) {
        std::cout << value << std::endl;
    });
}

void Application::Exit()
{

}

void Application::Event(SDL_Event event)
{

}

void Application::Update(double deltaTime)
{

}