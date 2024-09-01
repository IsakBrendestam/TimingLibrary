#include "Tween.h"

#include <iostream>


/*************************************
                Tween
**************************************/


Tween::Tween(float value):
    m_value(value), m_incValue(0), m_endValue(value), m_alive(true)
{

}

Tween* Tween::Create(float value)
{
    Tween* t = new Tween(value);
    TweenManager::tweens.push_back(t);
    return t;
}

void Tween::AddTimeFrameValue(float duration, float value)
{
    m_endValue += value;
    m_incValue = value/duration;
}

void Tween::AddUpdateFunction(std::function<void(float)> func)
{
    m_updateFunc = func;
}

void Tween::Upate(double deltaTime)
{
    if (m_value > m_endValue)
        m_alive = false;

    if (m_alive)
    {
        m_value += m_incValue * deltaTime;
        m_updateFunc(m_value);
    }
}

bool Tween::GetAlive()
{
    return m_alive;
}


/*************************************
             TweenManager
**************************************/


std::vector<Tween*> TweenManager::tweens;

void TweenManager::Update(double deltaTime)
{

    for (int i = tweens.size()-1; i >= 0; i--)
    {
        Tween* tween = tweens[i];
        if (tween->GetAlive())
            tween->Upate(deltaTime);
        else
        {
            delete tween;
            tweens.erase(tweens.begin() + i);
        }
    }
}

void TweenManager::Deconstruct()
{
    for (auto tween : tweens)
        delete tween;
}