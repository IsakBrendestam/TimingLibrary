#ifndef TWEEN_HEADER
#define TWEEN_HEADER

#include <vector>
#include <functional>
#include <queue>

enum FuncTypes
{
    Func_None,
    Func_Linear,
    Func_EaseInSine,
    Func_EaseOutSine,
    Func_EaseInOutSine,
    Func_EaseInQuad,
    Func_EaseOutQuad,
    Func_EaseInOutQuad,
    Func_EaseInCubic,
    Func_EaseOutCubic,
    Func_EaseInOutCubic,
    Func_EaseInQuart,
    Func_EaseOutQuart,
    Func_EaseInOutQuart,
    Func_EaseInQuint,
    Func_EaseOutQuint,
    Func_EaseInOutQuint,
    Func_EaseInExpo,
    Func_EaseOutExpo,
    Func_EaseInElastic,
    Func_EaseOutElastic,
    Func_EaseInOutElastic,
};

struct FrameInfo
{
    FrameInfo() = default;
    FrameInfo(float d, float v, FuncTypes ft):
        duration(d), value(v), funcType(ft)
    {};

    float duration;
    float value;
    FuncTypes funcType;
    float currentDuration = 0;
    float startValue = 0;
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

    void AddTimeFrameFunc(float duration, float value, FuncTypes type);

    void AddUpdateFunction(std::function<void(float)> func);
    void AddFrameFunction(unsigned int index, std::function<void(float)> func);
    void AddPercentageFunction(float fraction, std::function<void(float)> func);

    void Upate(double deltaTime);

    bool GetAlive();

private:
    void UpdateValue(double deltaTime);

private:
    Tween(float value);
    bool m_alive;

    std::queue<FrameInfo> m_frameQueue;
    FrameInfo m_currentFrame;

    std::function<void(float)> m_updateFunc; 
    std::vector<std::function<void(float)>> m_frameFunctions;
    std::function<void(float)> m_percentageFunc; 

    int m_currentFrameIndex;
    float m_value;
    float m_endDuration;
    float m_totalDuration;
    float m_percentageFraction;

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