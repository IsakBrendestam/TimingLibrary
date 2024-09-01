#ifndef TWEEN_HEADER
#define TWEEN_HEADER

#include <vector>
#include <functional>


/*************************************
                Tween
**************************************/


class Tween
{
public:
    ~Tween() = default;
public:
    static Tween* Create(float value);

    void AddTimeFrameValue(float duration, float value);

    void AddUpdateFunction(std::function<void(float)> func);

    void Upate(double deltaTime);

    bool GetAlive();

private:
    Tween(float value);
    bool m_alive;

    std::function<void(float)> m_updateFunc; 

    float m_value;
    float m_incValue;
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