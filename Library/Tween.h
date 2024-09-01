#ifndef TWEEN_HEADER
#define TWEEN_HEADER

#include <vector>


/*************************************
                Tween
**************************************/


class Tween
{
public:
    ~Tween() = default;
public:
    static Tween* Create(float value);

    void AddTimeFrame(float value);

    void AddUpdateFunction(void (*func)(float));

    void Upate(double deltaTime);

    float GetValue();

private:
    Tween(float value);

    void (*m_updateFunc)(float);

    float m_value;
    float m_endValue;
};


/*************************************
             TweenManager
**************************************/


class TweenManager
{
    friend class Tween;

public:
    static void Update(double deltaTime);
    static void Deconstruct();

private:
    static std::vector<Tween*> tweens;

};

#endif //TWEEN_HEADER