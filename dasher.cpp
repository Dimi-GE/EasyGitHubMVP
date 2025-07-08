#include "raylib.h"

//Window dimensions;
const int width {1280};
const int height {720};

//Acceleration due to gravity (pixels/s)/s;
const int gravity{1'000};


int main()
{
    InitWindow(width, height, "Dapper Dasher.");

    //Rectangle velocity;
    int velocity {0};

    //Nebula parameters
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{width, height - nebRec.height};

    //Nebula X velocity (pixels/sec)/s
    int nebVel{-600};

    //Scarfy's parametters
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    
    Rectangle scarfyRec;

    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;

    scarfyPos.x = width/2 - scarfyRec.width/2;
    scarfyPos.y = height - scarfyRec.height;

    //Frame
    int frame {};

    //Amount of time before update the animation time
    const float updateTime {1.0/12.0};
    float runningTime {};

    //Jump velocity(pixels/second)
    const int jumpVel {-600};

    //Is rectangle in the air
    bool isInAir {};

     while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        //Set FPS;
        SetTargetFPS(60);

        //Delta time(time since last frame(time between frames))
        const float DT{GetFrameTime()};

        //Perform ground check
        if (scarfyPos.y >= height - scarfyRec.height)
        {
            //Rectangle is on the ground;
            velocity = 0;
            DrawText("scarfyPos.y", 0, 0, 24, RED);
            isInAir = false;

            //Update animation per runningTime value related to the updateTime value(0.083333 = (1.0/12.0)) if not in the air
            if (runningTime >= updateTime)
            {
                DrawText(TextFormat("True"), 0, 90, 24, RED);
                runningTime = 0.0;

                //Update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }
        else
        {
            //Rectangle is in the air;
            velocity += gravity * DT;
            isInAir = true;

            //Freeze the animation on the jump sprite
            scarfyRec.x = 3;

            DrawText(TextFormat("Velocity = %i", velocity), 0, 0, 24, RED);
        }

        //Jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        //Update nebula's position
        nebPos.x += nebVel * DT;

        //Update Scarfy's position;
        scarfyPos.y += velocity * DT;

        //update running time
        runningTime += DT;
        DrawText(TextFormat("Running time = %f", runningTime), 0, 30, 24, RED);
        DrawText(TextFormat("Update time = %f", updateTime), 0, 60, 24, RED);


        //Draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        //Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        //End of the logic;
        EndDrawing();        
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

}