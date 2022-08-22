#include <cstdlib>
#include <iostream>
#include "Game.h"
#include <SDL2/SDL.h>

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

  TTF_Init();

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
  font = TTF_OpenFont("./assets/fonts/silkscreen.ttf", 48);
  if (!font) {
    std::cout << "Error opening font!" << std::endl;
  }

  double y = (windowHeight / 2.0) - 50.0;
  playerOne = std::make_unique<Player>(10, y, 15, 100.0, "P1");
  playerTwo = std::make_unique<Player>(windowWidth - 25, y, 15, 100.0, "P2");

  srand(time(NULL));

  double ballX = rand() % (windowWidth - 200) + 100;
  std::cout << "Ball X: " << ballX << std::endl;
  ball = std::make_unique<Ball>(ballX, 50);

  collisionSystem = std::make_unique<CollisionSystem>();
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
      case SDL_KEYUP:
        playerOne->OnKeyUp();
        playerTwo->OnKeyUp();
        break;
    }
  }
}

void Game::Update() {
  double newTime = SDL_GetTicks();

  int timeToWait = MILLISECONDS_PER_FRAME - (newTime - timeSinceLastUpdate);
  if (timeToWait > 0 && timeToWait <= MILLISECONDS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }

  double deltaTime = (newTime - timeSinceLastUpdate) / 1000.0;
  timeSinceLastUpdate = newTime;

  playerOne->Update(deltaTime, windowHeight);
  playerTwo->Update(deltaTime, windowHeight);
  ball->Update(deltaTime, windowWidth, windowHeight);

  collisionSystem->CheckCollision(playerOne, playerTwo, ball, windowWidth, windowHeight);
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
  playerOne->RenderScore(renderer, font, windowWidth);
  playerTwo->RenderScore(renderer, font, windowWidth);

  SDL_RenderPresent(renderer);
}

void Game::Destroy() {
  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

