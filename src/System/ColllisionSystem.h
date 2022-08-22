#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <memory.h>
#include "../Entity/Player.h"
#include "../Entity/Ball.h"

class CollisionSystem {
  public:
    CollisionSystem() = default;
    ~CollisionSystem() = default;

    void CheckCollision(
        std::unique_ptr<Player>& playerOne,
        std::unique_ptr<Player>& playerTwo,
        std::unique_ptr<Ball>& ball,
        const int& windowWidth,
        const int& windowHeight
    ) {

      time_t timer;
      time(&timer);

      // Ball collided with player one
      if ((ball->x <= playerOne->x + playerOne->width) &&
          (ball->y + ball->height >= playerOne->y) &&
          (ball->y <= playerOne->y + playerOne->height)) {
        std::cout << "Ball collided with " << playerOne->tag << std::endl;
        ball->dx = 100;
        if (ball->y > playerOne->height / 2) {
          ball->dy = timer % 2 == 0 ? 100 : -100;
        } else {
          ball->dy = timer % 2 == 0 ? -100 : 100;
        }
        return;
      }

      // Ball collided with player two
      if ((ball->x + ball->width >= playerTwo->x) &&
          (ball->y + ball->height >= playerTwo->y) &&
          (ball->y <= playerTwo->y + playerTwo->height)) {
        std::cout << "Ball collided with " << playerTwo->tag << std::endl;
        ball->dx = -100;
        if (ball->y > playerTwo->height / 2) {
          ball->dy = timer % 2 == 0 ? -100 : 100;
        } else {
          ball->dy = timer % 2 == 0 ? 100 : -100;
        }
        return;
      }

      if (ball->y <= 0) {
        ball->dy = 100;
        std::cout << "Ball collided with wall top dx: " << ball->dx << " dy: " << ball->dy << std::endl;
        return;
      }

      if (ball->y + ball->height >= windowHeight) {
        ball->dy = -100;
        std::cout << "Ball collided with wall bottom dx: " << ball->dx << " dy: " << ball->dy << std::endl;
        return;
      }

      // Ball collided with boundaries
      if (ball->x <= 0 ||
          ball->x + ball->width >= windowWidth) {

        if (ball->x <= 0) {
          playerTwo->score += 1;
        } else {
          playerOne->score += 1;
        }

        srand(time(NULL));

        double ballX = rand() % (windowWidth - 200) + 100;
        double ballY = rand() % (windowHeight / 2) + 10;

        ball->x = ballX;
        ball->y = ballY;
      }
    }
};

#endif
