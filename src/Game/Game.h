#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
  private:
    bool isRunning;
    int windowWidth;
    int windowHeight;

    SDL_Window* window;
    SDL_Renderer* renderer;

  public:
    Game();
    ~Game();

    void Init();
    void Run();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};

#endif
