#include "Tween.h"

std::vector<Tween*> TweenManager::tweens;

void TweenManager::Update(double deltaTime)
{
    for (auto tween : tweens)
        tween->Upate(deltaTime);
}

void TweenManager::Deconstruct()
{
    for (auto tween : tweens)
        delete tween;
}



Tween::Tween(float value):
    m_value(value)
{

}

Tween* Tween::Create(float value)
{
    Tween* t = new Tween(value);
    TweenManager::tweens.push_back(t);
    return t;
}

void Tween::AddUpdateFunction(void (*func)(float))
{
    m_updateFunc = func;
}

void Tween::Upate(double deltaTime)
{
    m_value += deltaTime;
    m_updateFunc(m_value);
}

float Tween::GetValue()
{
    return m_value;
}