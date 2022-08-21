#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

class Ball {
  private:
    double x;
    double y;

  public:
    Ball(double x, double y) {
      this->x = x;
      this->y = y;
    }

    void Update(double deltaTime, int windowWidth, int windowHeight) {
      this->x += 100 * deltaTime;
      this->y += 100 * deltaTime;
    }

    void Render(SDL_Renderer* renderer) {
      SDL_Rect rect = {
        static_cast<int>(this->x),
        static_cast<int>(this->y),
        15,
        15
      };
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderFillRect(renderer, &rect);
    }
};

#endif
