#ifndef PLAYER_H
#define PLAYER_H

#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstring>
#include <iostream>

class Player {
  public:
    double x;
    double y;
    double width;
    double height;
    double velocity = 0;
    int score = 0;
    std::string tag;

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
          this->velocity = -100;
        } else if (symbol == SDLK_s) {
          this->velocity = 100;
        }
      } else {
        if (symbol == SDLK_UP) {
          this->velocity = -100;
        } else if (symbol == SDLK_DOWN) {
          this->velocity = 100;
        }
      }
    }

    void OnKeyUp() {
      this->velocity = 0;
    }

    void Update(double deltaTime, int windowHeight) {
      this->y += round(this->velocity * deltaTime);
      if (this->y < 10) {
        this->y = 10;
      } else if (this->y + this->height >= windowHeight - 10) {
        this->y = windowHeight - this->height - 10;
      }
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

    void RenderScore(SDL_Renderer* renderer, TTF_Font* font, const int& windowWidth) {
      SDL_Color color = {255, 255, 255};
      SDL_Surface* surface = TTF_RenderText_Blended(font, std::to_string(this->score).c_str(), color);
      SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_FreeSurface(surface);

      int textHeight = 0;
      int textWidth = 0;
      SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

      int x = 0;
      if (this->x < windowWidth / 2.0) {
        x = windowWidth / 4;
      } else {
        x = (windowWidth / 4) * 3;
      }


      SDL_Rect textRect = {
        x,
        10,
        textWidth,
        textHeight
      };

      SDL_RenderCopy(renderer, texture, NULL, &textRect);
      SDL_DestroyTexture(texture);
    }
};

#endif
