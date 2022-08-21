#include <cstdlib>
#include <iostream>
#include "Game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"

Game::Game() {
  isRunning = false;
  std::cout << "Game constructor called!" << std::endl;
}

Game::~Game() {
  std::cout << "Game destructor called!" << std::endl;
}

void Game::Init() {
  windowWidth = 800;
  windowHeight = 600;

  SDL_Init(SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow(
    "Pong",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    windowWidth,
    windowHeight,
    0
  );

  if (!window) {
    std::cout << "Error creating SDL Window!" << std::endl;
    return;
  }

  renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );

  if (!renderer) {
    std::cout << "Error creating SDL Renderer!" << std::endl;
    return;
  }

  isRunning = true;
}

void Game::Run() {
  SetUp();
  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
}

void Game::SetUp() {
  double y = (windowHeight / 2.0) - 50.0;
  playerOne = std::make_unique<Player>(10, y, 15, 100.0, "P1");
  playerTwo = std::make_unique<Player>(windowWidth - 25, y, 15, 100.0, "P2");

  srand(time(NULL));

  double ballX = rand() % (windowWidth - 200) + 100;
  std::cout << "Ball X: " << ballX << std::endl;
  ball = std::make_unique<Ball>(ballX, 50);
}

void Game::ProcessInput() {
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
      case SDL_QUIT:
        isRunning = false;
        break;
      case SDL_KEYDOWN:
        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
          isRunning = false;
        }
        playerOne->OnKeyDown(sdlEvent.key.keysym.sym);
        playerTwo->OnKeyDown(sdlEvent.key.keysym.sym);
        break;
    }
  }
}

void Game::Update() {
  int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - timeSinceLastUpdate);
  if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }

  double deltaTime = (SDL_GetTicks() - timeSinceLastUpdate) / 1000.0;
  timeSinceLastUpdate = SDL_GetTicks();

  playerOne->Update(deltaTime, windowHeight);
  playerTwo->Update(deltaTime, windowHeight);
  ball->Update(deltaTime, windowWidth, windowHeight);
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);

  int x = windowWidth / 2;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 155);
  SDL_RenderDrawLine(renderer, x, 0, x, windowHeight);

  playerOne->Render(renderer);
  playerTwo->Render(renderer);
  ball->Render(renderer);

  SDL_RenderPresent(renderer);
}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

