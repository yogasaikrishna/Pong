#ifndef GAME_H
#define GAME_H

#include <memory>
#include <SDL2/SDL.h>
#include "../Entity/Player.h"
#include "../Entity/Ball.h"

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Game {
  private:
    bool isRunning;
    int windowWidth;
    int windowHeight;
    int timeSinceLastUpdate = 0;

    std::unique_ptr<Player> playerOne;
    std::unique_ptr<Player> playerTwo;
    std::unique_ptr<Ball> ball;

    SDL_Window* window;
    SDL_Renderer* renderer;

  public:
    Game();
    ~Game();

    void Init();
    void SetUp();
    void Run();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};

#endif
