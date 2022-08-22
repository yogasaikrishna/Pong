#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

class Ball {
  public:
    double x;
    double y;
    int width = 15;
    int height = 15;
    int dx = 100;
    int dy = 100;

    Ball(double x, double y) {
      this->x = x;
      this->y = y;
    }

    void Update(double deltaTime, int windowWidth, int windowHeight) {
      this->x += this->dx * deltaTime;
      this->y += this->dy * deltaTime;
    }

    void Render(SDL_Renderer* renderer) {
      SDL_Rect rect = {
        static_cast<int>(this->x),
        static_cast<int>(this->y),
        width,
        height
      };
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(renderer, &rect);
    }
};

#endif
