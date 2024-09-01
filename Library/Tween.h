#ifndef TWEEN_HEADER
#define TWEEN_HEADER

class Tween
{
public:
    Tween(float value);

    void Upate(double deltaTime);

    float GetValue();

private:
    float m_value;

};

#endif //TWEEN_HEADER