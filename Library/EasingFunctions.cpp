#include "EasingFunctions.h"

#include <cmath>

float EaseInCubic(float fraction)
{
    return pow(fraction, 3);
}

float EaseOutCubic(float fraction)
{
    return 1 - pow(1 - fraction, 3);
}

float EaseInOutCubic(float fraction)
{
    if (fraction < 0.5f)
        return 4 * pow(fraction, 3);
    return 1 - pow(-2 * fraction + 2, 3) / 2;
}

float EaseInElastic(float fraction)
{
    const float  c4 = (2 * M_PI) / 3;
    if (fraction == 0)
        return 0;
    else if (fraction == 1)
        return 1;
    return -pow(2, 10 * fraction - 10) * sin((fraction * 10 - 10.75) * c4);
}

float EaseInOutElastic(float fraction)
{
    const float c5 = 2 * M_PI / 4.5f; 
    if (fraction == 0)
        return 0;
    else if (fraction >= 1)
        return 1;
    else if (fraction < 0.5f)
        return (-(pow(2, 20 * fraction - 10) * sin((20 * fraction - 11.125f) * c5)) / 2);
    return ((pow(2, -20 * fraction + 10) * sin((20 * fraction - 11.125f) * c5)) / 2 + 1);
}