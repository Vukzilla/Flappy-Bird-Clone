#include "raylib.h"
#include <iostream>

int main(void)
{

    const int screenWidth = 288;
    const int screenHeight = 512;

    InitWindow(screenWidth, screenHeight, "Flappy Bird");

    Image iconImage = LoadImage("./fb/icon.png");

    SetWindowIcon(iconImage);

    UnloadImage(iconImage);

    Texture2D background = LoadTexture("./fb/background-day.png");
    Texture2D background_night = LoadTexture("./fb/background-night.png");
    Texture2D ground_texture = LoadTexture("./fb/base.png");
    Texture2D pipe_texture = LoadTexture("./fb/pipe-green.png");
    Texture2D pipe_upsidedown_texture = LoadTexture("./fb/pipe-green-upsidedown.png");
    Texture2D message_texture = LoadTexture("./fb/message.png");
    Texture2D gameover_texture = LoadTexture("./fb/gameover.png");

    Texture2D blue_bird_texture = LoadTexture("./fb/bluebird-midflap.png");
    Texture2D blue_bird_texture_down = LoadTexture("./fb/bluebird-downflap.png");
    Texture2D blue_bird_texture_up = LoadTexture("./fb/bluebird-upflap.png");
    Texture2D red_bird_texture = LoadTexture("./fb/redbird-midflap.png");
    Texture2D red_bird_texture_down = LoadTexture("./fb/redbird-downflap.png");
    Texture2D red_bird_texture_up = LoadTexture("./fb/redbird-upflap.png");
    Texture2D yellow_bird_texture = LoadTexture("./fb/yellowbird-midflap.png");
    Texture2D yellow_bird_texture_down = LoadTexture("./fb/yellowbird-downflap.png");
    Texture2D yellow_bird_texture_up = LoadTexture("./fb/yellowbird-upflap.png");

    //Sound flap = LoadSound("./fb/flap.wav");

    SetTargetFPS(60);

    float x = screenWidth / 8;
    float y = screenHeight / 2;

    bool dead = false;
    bool score_bool = true;
    bool start_game = false;

    bool red = false;
    bool yellow = false;
    bool blue = false;
    bool unlocked_flap = false;


    float x_pipe = 500;
    float y_pipe = 160;

    float x_pipe1 = 1000;
    float y_pipe1 = 160;

    float x_ground = 0;

    float x_ground1 = screenWidth;

    float gravity = 0.25;
    float velocity = 0;

    int score = 0;
    int currentTime = 0;
    int rng_bg = GetRandomValue(1, 2);
    int rng_bird = GetRandomValue(1, 3);

    Rectangle ground{ 0,  400, 336 , 112 };

    y_pipe = GetRandomValue(150, 300);
    y_pipe1 = GetRandomValue(150, 300);

    while (!WindowShouldClose()) //Update
    {

        if (!dead && start_game)
        {
            velocity += gravity;
            y += velocity;
            x_pipe -= 3;
            x_pipe1 -= 3;
            x_ground -= 3;
            x_ground1 -= 3;
        }

        BeginDrawing();

        Rectangle player{ x, y, 34, 24 };
        Rectangle pipe_lower{ x_pipe, y_pipe, 52, 320 };
        Rectangle pipe_upper{ x_pipe, y_pipe - 420, 52, 320 };
        Rectangle pipe_lower1{ x_pipe1, y_pipe1, 52, 320 };
        Rectangle pipe_upper1{ x_pipe1, y_pipe1 - 420, 52, 320 };
        if (rng_bg == 1)
        {
            DrawTexture(background, 0, 0, WHITE);
        }
        else
        {
            DrawTexture(background_night, 0, 0, WHITE);
        }

        if (rng_bird == 1)
        {                  
            red = true;
            blue = false;
            yellow = false;
        }
        if (rng_bird == 2)
        {
            red = false;
            blue = true;
            yellow = false;
        }
        if (rng_bird == 3)
        {
            red = false;
            blue = false;
            yellow = true;
        }

        DrawTexture(pipe_texture, x_pipe, y_pipe, WHITE);
        DrawTexture(pipe_upsidedown_texture, x_pipe, y_pipe - 420, WHITE);
        DrawTexture(pipe_texture, x_pipe1, y_pipe1, WHITE);
        DrawTexture(pipe_upsidedown_texture, x_pipe1, y_pipe1 - 420, WHITE);
        DrawTexture(ground_texture, x_ground, 400, WHITE);
        DrawTexture(ground_texture, x_ground1, 400, WHITE);

        if (blue)
        {
            DrawTexture(blue_bird_texture, x, y, WHITE);
        }
        if (red)
        {
            DrawTexture(red_bird_texture, x, y, WHITE);
        }
        if (yellow)
        {
            DrawTexture(yellow_bird_texture, x, y, WHITE);
        }

        if (start_game)
        {
            DrawText(TextFormat("%i", score), screenWidth / 2 - 20, 60, 75, WHITE);
        }
        else
        {
            DrawTexture(message_texture, 50, 100, WHITE);
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentTime = 0;
            start_game = true;
            velocity = -5.6;
            //PlaySound(flap);
            unlocked_flap = true;
        }

        if (currentTime <= 60)
        {
            currentTime += 1;
        }

        if (currentTime <= 5 && blue && unlocked_flap)
        {
            DrawTexture(blue_bird_texture_up, x, y, WHITE);
        }
        if (currentTime >= 4 && currentTime <= 10 && blue && unlocked_flap)
        {
            DrawTexture(blue_bird_texture_down, x, y, WHITE);
        }
        if (currentTime <= 5 && red && unlocked_flap)
        {
            DrawTexture(red_bird_texture_up, x, y, WHITE);
        }
        if (currentTime >= 4 && currentTime <= 10 && red && unlocked_flap)
        {
            DrawTexture(red_bird_texture_down, x, y, WHITE);
        }
        if (currentTime <= 5 && yellow && unlocked_flap)
        {
            DrawTexture(yellow_bird_texture_up, x, y, WHITE);
        }
        if (currentTime >= 4 && currentTime <= 10 && yellow && unlocked_flap)
        {
            DrawTexture(yellow_bird_texture_down, x, y, WHITE);
        }

        if (x_pipe <= -50)
        {
            y_pipe = GetRandomValue(100, 300);

            x_pipe = screenWidth;
            score_bool = true;
        }
        if (x_pipe1 <= -50)
        {
            y_pipe1 = GetRandomValue(100, 300);

            x_pipe1 = screenWidth;
            score_bool = true;
        }

        if (x_ground <= -screenWidth)
        {
            x_ground = screenWidth;
        }
        if (x_ground1 <= -screenWidth)
        {
            x_ground1 = screenWidth;
        }


        if ((x >= x_pipe || x >= x_pipe1) && score_bool)
        {
            score_bool = false;
            score += 1;
        }

        if (CheckCollisionRecs(player, pipe_lower) || CheckCollisionRecs(player, pipe_upper) || CheckCollisionRecs(player, pipe_lower1) || CheckCollisionRecs(player, pipe_upper1) || CheckCollisionRecs(player, ground))
        {
            dead = true;
            DrawTexture(gameover_texture, screenWidth / 2 - 100, 135, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {            
                score_bool = true;
                x = screenWidth / 8;
                y = screenHeight / 2;
                x_pipe = 500;
                y_pipe = 160;
                x_pipe1 = 1000;
                y_pipe1 = 160;
                score = 0;
                rng_bg = GetRandomValue(1, 2);
                rng_bird = GetRandomValue(1, 3);
                std::cout << rng_bird << std::endl;
                dead = false;
            }
        }

        EndDrawing();
    }

    UnloadTexture(blue_bird_texture);
    UnloadTexture(blue_bird_texture_down);
    UnloadTexture(blue_bird_texture_up);
    UnloadTexture(red_bird_texture);
    UnloadTexture(red_bird_texture_down);
    UnloadTexture(red_bird_texture_up);
    UnloadTexture(yellow_bird_texture);
    UnloadTexture(yellow_bird_texture_down);
    UnloadTexture(yellow_bird_texture_up);

    UnloadTexture(background);
    UnloadTexture(ground_texture);
    UnloadTexture(pipe_texture);
    UnloadTexture(message_texture);
    UnloadTexture(pipe_upsidedown_texture);
    UnloadTexture(gameover_texture);

    //UnloadSound(flap);

    CloseWindow();

    return 0;
}
