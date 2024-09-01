#include "Tween.h"

Tween::Tween(float value):
    m_value(value)
{
}

void Tween::Upate(double deltaTime)
{
    m_value += deltaTime;
}

float Tween::GetValue()
{
    return m_value;
}