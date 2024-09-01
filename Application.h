#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include <SDL2/SDL.h>

class Application
{
public:
    Application() = default;
    ~Application() = default;

    void Init();
    void Exit();

    void Event(SDL_Event event);
    void Update(double deltaTime);

private:
};

#endif //APPLICATION_HEADER