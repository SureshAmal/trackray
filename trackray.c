#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ScreenHeight 500
#define ScreenWidth 600
#define BALL_RADIUS 40
#define NumberOFBall 10
#define BG_COLOR RED

int rand_sign() { return rand() % 2 == 0 ? -1 : 1; }

typedef struct ball {
  Vector2 position;
  Vector2 velocity;
} Ball;

typedef struct {
  int x;
  int y;
  int width;
  int height;
} Rect;

int inside_rect(int x, int y, int width, int height, Ball ball,
                int ball_radius) {
  if (ball.position.x + ball_radius > x &&
      ball.position.x - ball_radius < width + x &&
      ball.position.y + ball_radius > y &&
      ball.position.y - ball_radius < height + y) {
    return 1;
  }

  return 0;
}

int main(void) {
  srand(time(NULL));
  Vector2 gravity = {0.0f, 980.0f};
  Ball Balls[NumberOFBall];
  Color colors[NumberOFBall];
  Rect rect = {160, 300, 100, 100};

  for (int i = 0; i < NumberOFBall; i++) {
    colors[i] = ColorFromHSV((float)(rand() % 360), 1, 20);
    Balls[i].position = (Vector2){(float)(rand() % (ScreenWidth - 50)),
                                  (float)(rand() % (ScreenHeight - 50))};
    Balls[i].velocity = (Vector2){(float)(rand_sign() * rand() % 90), 0.0f};
  }

  InitWindow(ScreenWidth, ScreenHeight, "Time Pass");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    float floorY = (float)ScreenHeight - BALL_RADIUS;
    for (int i = 0; i < NumberOFBall; i++) {
      Balls[i].velocity.y += gravity.y * dt;
      Balls[i].position.y += Balls[i].velocity.y * dt;
      Balls[i].position.x += Balls[i].velocity.x * dt;
      float currentBallRadius = BALL_RADIUS;
      if (Balls[i].position.y >= (float)ScreenHeight - currentBallRadius) {
        Balls[i].position.y = (float)ScreenHeight - currentBallRadius;
        Balls[i].velocity.y *= -0.95f;
      }
      if (Balls[i].position.x >= (float)ScreenWidth - currentBallRadius) {
        Balls[i].position.x = (float)ScreenWidth - currentBallRadius;
        Balls[i].velocity.x *= -0.90f;
      } else if (Balls[i].position.x <= currentBallRadius) {
        Balls[i].position.x = currentBallRadius;
        Balls[i].velocity.x *= -0.90f;
      }

      if (inside_rect(rect.x, rect.y, rect.width, rect.height, Balls[i],
                      BALL_RADIUS)) {
        Balls[i].velocity.y *= -0.90f;
      }
    }

    BeginDrawing();
    ClearBackground(BG_COLOR);
    DrawLine(0, (int)floorY + BALL_RADIUS, ScreenWidth,
             (int)floorY + BALL_RADIUS, BLACK);

    for (int i = 0; i < NumberOFBall; i++) {
      DrawCircle((int)Balls[i].position.x, (int)Balls[i].position.y,
                 BALL_RADIUS, colors[i]);
    }
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, BLACK);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
