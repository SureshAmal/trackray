#include "raylib.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define ScreenHeight 500
#define ScreenWidth 600
#define BALL_RADIUS 10
#define NumberOFBall 10000
#define BG_COLOR RED

int rand_sign() { return rand() % 2 == 0 ? -1 : 1; }

typedef struct ball {
  Vector2 position;
  Vector2 velocity;
} Ball;

// return 0 if no collision
// return 1 if up or down collision
// return 2 if left or right collision
int inside_rect(Rectangle rect, Ball current_ball, Ball prev_ball,
                int ball_radius) {
  bool is_collide =
      CheckCollisionCircleRec(current_ball.position, ball_radius, rect);
  if (prev_ball.position.y + ball_radius > rect.y &&
      prev_ball.position.y < rect.y + rect.height) {
    if (is_collide)
      return 2;
  } else {
    if (is_collide)
      return 1;
  }

  return 0;
}

int main(void) {
  srand(time(NULL));
  Vector2 gravity = {0.0f, 980.0f};
  Ball Balls[NumberOFBall];
  Color colors[NumberOFBall];
  Rectangle rect[10] = {
      {160, 400, 50, 50}, {400, 400, 50, 50}, {100, 200, 50, 50},
      {200, 250, 50, 50}, {300, 200, 50, 50}, {400, 200, 50, 50},
      {400, 400, 50, 50}, {100, 300, 50, 50}, {300, 400, 50, 50}};

  for (int i = 0; i < NumberOFBall; i++) {
    colors[i] = ColorFromHSV((float)(rand() % 360), 60, 40);
    Balls[i].position =
        (Vector2){(float)(rand() % (ScreenWidth)), (float)(rand() % (100))};
    Balls[i].velocity = (Vector2){(float)(rand_sign() * rand() % 90), 0.0f};
  }

  InitWindow(ScreenWidth, ScreenHeight, "Time Pass");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    float floorY = (float)ScreenHeight - BALL_RADIUS;
    for (int i = 0; i < NumberOFBall; i++) {
      Ball prev_ball = Balls[i];
      Balls[i].velocity.y += gravity.y * dt;
      Balls[i].position.y += Balls[i].velocity.y * dt;
      Balls[i].position.x += Balls[i].velocity.x * dt;
      float currentBallRadius = BALL_RADIUS;
      if (Balls[i].position.y >= (float)ScreenHeight - currentBallRadius) {
        Balls[i].position.y = (float)ScreenHeight - currentBallRadius;
        Balls[i].velocity.y *= -0.97f;
      }
      if (Balls[i].position.x >= (float)ScreenWidth - currentBallRadius) {
        Balls[i].position.x = (float)ScreenWidth - currentBallRadius;
        Balls[i].velocity.x *= -0.96f;
      } else if (Balls[i].position.x <= currentBallRadius) {
        Balls[i].position.x = currentBallRadius;
        Balls[i].velocity.x *= -0.95f;
      }
      for (int j = 0; j < 10; j++) {
        if (inside_rect(rect[j], Balls[i], prev_ball, BALL_RADIUS) == 1) {
          Balls[i].velocity.y *= -0.90f;
          if (Balls[i].position.y < rect[j].y) {
            Balls[i].position.y = rect[j].y - BALL_RADIUS;
          } else {
            Balls[i].position.y = rect[j].y + rect[j].height + BALL_RADIUS;
          }
        }
        if (inside_rect(rect[j], Balls[i], prev_ball, BALL_RADIUS) == 2) {
          Balls[i].velocity.x *= -0.90f;
          if (Balls[i].position.x < rect[j].x + rect[j].width / 2) {
            Balls[i].position.x = rect[j].x - BALL_RADIUS;
          } else {
            Balls[i].position.x = rect[j].x + rect[j].width + BALL_RADIUS;
          }
        }
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
    for (int i = 0; i < 10; i++) {
      DrawRectangle(rect[i].x, rect[i].y, rect[i].width, rect[i].height, BLACK);
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
