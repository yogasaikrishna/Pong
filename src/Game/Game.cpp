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
  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
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
        break;
    }
  }
}

void Game::Update() {

}

void Game::Render() {

}

void Game::Destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

