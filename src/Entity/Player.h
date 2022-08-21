#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <cstring>
#include <iostream>

enum Movement {
  UP,
  DOWN,
  NONE
};

class Player {
  private:
    double x;
    double y;
    double width;
    double height;
    std::string tag;
    Movement direction = NONE;

  public:
    Player(double x, double y, double width, double height, const std::string& tag) {
      this->x = x;
      this->y = y;
      this->width = width;
      this->height = height;
      this->tag = tag;
    }

    void OnKeyDown(SDL_Keycode symbol) {
      if (std::strcmp(this->tag.c_str(), "P1") == 0) {
        if (symbol == SDLK_w) {
          this->direction = UP;
        } else if (symbol == SDLK_s) {
          this->direction = DOWN;
        }
      } else {
        if (symbol == SDLK_UP) {
          this->direction = UP;
        } else if (symbol == SDLK_DOWN) {
          this->direction = DOWN;
        }
      }
    }

    void Update(double deltaTime, int windowHeight) {
      if (this->direction == UP) {
        this->y -= 300.0 * deltaTime;
        std::cout << this->tag << " UP y: " << this->y << " DT: " << deltaTime << std::endl;
      } else if (this->direction == DOWN) {
        this->y += 300 * deltaTime;
        std::cout << this->tag << " DOWN y: " << this->y << " DT: " << deltaTime << std::endl;
      }
      if (this->y < 10) {
        this->y = 10;
      } else if (this->y + this->height >= windowHeight - 10) {
        this->y = windowHeight - this->height - 10;
      }
      this->direction = NONE;
    }

    void Render(SDL_Renderer* renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_Rect rect = {
        static_cast<int>(this->x),
        static_cast<int>(this->y),
        static_cast<int>(this->width),
        static_cast<int>(this->height)
      };
      SDL_RenderFillRect(renderer, &rect);
    }
};

#endif
