#include "Tween.h"

#include <iostream>
#include <cmath>
#include "EasingFunctions.h"


/*************************************
                Tween
**************************************/


Tween::Tween(float value):
    m_value(value), m_incValue(0), m_endDuration(0), m_alive(true), m_currentFuncType(Func_None),
    m_currentDuration(0), m_totalDuration(0), m_funcStartValue(value)
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
    m_endDuration += duration;
    m_incValue = value;
    m_funcDuration = duration;
}

void Tween::AddTimeFrameFunc(float duration, float value, FuncTypes type)
{
    m_endDuration += duration;
    m_incValue = value;
    m_funcDuration = duration;
    m_currentDuration = 0;
    m_currentFuncType = type;
}

void Tween::AddUpdateFunction(std::function<void(float)> func)
{
    m_updateFunc = func;
}

void Tween::UpdateValue(double deltaTime)
{
    m_currentDuration += deltaTime;

    const float animationFactor = m_currentDuration / m_funcDuration;

    std::cout << animationFactor << std::endl;

    switch (m_currentFuncType)
    {
    case Func_None:
        break;

    case Func_Linear:
        m_value += m_incValue * animationFactor;
        break;

    case Func_EaseInOutElastic:
        m_value = m_funcStartValue + m_incValue * EaseInOutElastic(animationFactor);
        break;

    case Func_EaseInCubic:
        m_value = m_funcStartValue + m_incValue * EaseInCubic(animationFactor);
    default:
        break;
    }
}

void Tween::Upate(double deltaTime)
{
    if (m_totalDuration > m_endDuration)
        m_alive = false;

    m_totalDuration += deltaTime;

    if (m_alive)
    {
        UpdateValue(deltaTime);
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