#ifndef TWEEN_HEADER
#define TWEEN_HEADER

#include <vector>
#include <functional>

enum FuncTypes
{
    Func_None,
    Func_Linear,
    Func_EaseInOutElastic,
    Func_EaseInCubic,
};



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
    void AddTimeFrameFunc(float duration, float value, FuncTypes type);

    void AddUpdateFunction(std::function<void(float)> func);

    void Upate(double deltaTime);

    bool GetAlive();

private:
    void UpdateValue(double deltaTime);

private:
    Tween(float value);
    bool m_alive;

    std::function<void(float)> m_updateFunc; 
    FuncTypes m_currentFuncType;

    float m_value;
    float m_incValue;
    float m_funcStartValue;
    float m_endDuration;
    float m_funcDuration;
    float m_currentDuration;
    float m_totalDuration;
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