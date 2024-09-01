#ifndef TWEEN_HEADER
#define TWEEN_HEADER

class Tween
{
public:
    Tween(float startingValue);

    float GetValue();

private:
    float m_startingValue;

};

#endif //TWEEN_HEADER