#include "Tween.h"

#include <iostream>
#include <cmath>
#include "EasingFunctions.h"


/*************************************
                Tween
**************************************/


Tween::Tween(float value):
    m_value(value), m_endDuration(0), m_alive(true),
    m_totalDuration(0), m_currentFrameIndex(-1), 
    m_percentageFraction(-1)
{
    m_currentFrame = FrameInfo(0, 0, Func_None);
    m_updateFunc = nullptr;
    m_percentageFunc = nullptr;
}

Tween* Tween::Create(float value)
{
    Tween* t = new Tween(value);
    TweenManager::tweens.push_back(t);
    return t;
}

void Tween::AddTimeFrameFunc(float duration, float value, FuncTypes type)
{
    m_frameQueue.push(FrameInfo(duration, value, type));
    m_frameFunctions.push_back(nullptr);
    m_endDuration += duration;
}

void Tween::AddUpdateFunction(std::function<void(float)> func)
{
    m_updateFunc = func;
}

void Tween::AddFrameFunction(unsigned int index, std::function<void(float)> func)
{
    if (index < m_frameFunctions.size())
        m_frameFunctions[index] = func;
}

void Tween::AddPercentageFunction(float fraction, std::function<void(float)> func)
{
    m_percentageFraction = fraction;
    m_percentageFunc = func;
}

void Tween::UpdateValue(double deltaTime)
{
    m_currentFrame.currentDuration += deltaTime;

    const float animationFactor = m_currentFrame.currentDuration / m_currentFrame.duration;

    switch (m_currentFrame.funcType)
    {
    case Func_None:
        break;
    case Func_Linear:
        m_value = m_currentFrame.startValue + m_currentFrame.value * animationFactor;
        break;
    case Func_EaseInSine:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseInSine(animationFactor);
        break;
    case Func_EaseOutSine:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseOutSine(animationFactor);
        break;
    case Func_EaseInOutSine:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseInOutSine(animationFactor);
        break;
    case Func_EaseInQuad:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseInQuad(animationFactor);
        break;
    case Func_EaseOutQuad:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseOutQuad(animationFactor);
        break;
    case Func_EaseInCubic:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseInCubic(animationFactor);
        break;
    case Func_EaseOutCubic:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseOutCubic(animationFactor);
        break;
    case Func_EaseInOutCubic:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseInOutCubic(animationFactor);
        break;
    case Func_EaseInElastic:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseInOutElastic(animationFactor);
        break;
    case Func_EaseOutElastic:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseOutElastic(animationFactor);
        break;
    case Func_EaseInOutElastic:
        m_value = m_currentFrame.startValue + m_currentFrame.value * EaseInOutElastic(animationFactor);
        break;
    default:
        break;
    }
}

void Tween::Upate(double deltaTime)
{
    if (m_currentFrame.currentDuration >= m_currentFrame.duration)
    {
        if (m_frameQueue.size() > 0)
        {
            m_currentFrameIndex++;
            m_currentFrame = m_frameQueue.front();
            m_currentFrame.startValue = m_value;
            m_frameQueue.pop();
        }
    }

    if (m_totalDuration > m_endDuration)
        m_alive = false;

    m_totalDuration += deltaTime;

    if (m_alive)
    {
        UpdateValue(deltaTime);

        if (m_currentFrameIndex != -1 && m_currentFrameIndex < m_frameFunctions.size())
            if (m_frameFunctions[m_currentFrameIndex] != nullptr) 
            {
                std::function<void(float)> f = m_frameFunctions[m_currentFrameIndex];
                f(m_value);
            }
    
        if (m_updateFunc != nullptr)
            m_updateFunc(m_value);

        if (m_percentageFraction != -1 && m_percentageFunc != nullptr)
            if ((m_currentFrame.currentDuration / m_currentFrame.duration) > m_percentageFraction)
                m_percentageFunc(m_value);

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