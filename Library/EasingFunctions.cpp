#include "EasingFunctions.h"

#include <cmath>

const float c4 = (2 * M_PI) / 3;
const float c5 = 2 * M_PI / 4.5f; 

float EaseInSine(float fraction)
{
    return 1 - cos((fraction * M_PI) / 2);
}

float EaseOutSine(float fraction)
{
    return sin((fraction * M_PI) / 2);
}

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
    if (fraction == 0)
        return 0;
    else if (fraction == 1)
        return 1;
    return -pow(2, 10 * fraction - 10) * sin((fraction * 10 - 10.75) * c4);
}

float EaseOutElastic(float fraction)
{
    if (fraction == 0)
        return 0;
    else if (fraction == 1)
        return 1;

    return -pow(2, 10 * fraction - 10) * sin((fraction * 10 - 10.75f) * c4);
}

float EaseInOutElastic(float fraction)
{
    if (fraction == 0)
        return 0;
    else if (fraction >= 1)
        return 1;
    else if (fraction < 0.5f)
        return (-(pow(2, 20 * fraction - 10) * sin((20 * fraction - 11.125f) * c5)) / 2);
    return ((pow(2, -20 * fraction + 10) * sin((20 * fraction - 11.125f) * c5)) / 2 + 1);
}