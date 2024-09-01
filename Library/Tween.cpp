#include "Tween.h"

Tween::Tween(float startingValue):
    m_startingValue(startingValue)
{
}

float Tween::GetValue()
{
    return m_startingValue;
}