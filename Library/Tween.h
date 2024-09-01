#ifndef TWEEN_HEADER
#define TWEEN_HEADER

#include <vector>

class Tween
{
public:
    static Tween* Create(float value);

    void AddUpdateFunction(void (*func)(float));

    void Upate(double deltaTime);

    float GetValue();

private:
    Tween(float value);

    void (*m_updateFunc)(float);

    float m_value;
};


class TweenManager
{
public:
    static void Update(double deltaTime);
    static void Deconstruct();

private:
    static std::vector<Tween*> tweens;

    friend class Tween;
};

#endif //TWEEN_HEADER