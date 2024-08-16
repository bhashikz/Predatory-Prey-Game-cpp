#include "raylib.h"
#include "raymath.h" // Functions used Vector2Add, Vector2Subtract, Vector2Normalize, Vector2Scale
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    int windowDimensions[2];   // Array of window dimension
    windowDimensions[0] = 384; // Window Width
    windowDimensions[1] = 384; // Window Height

    InitWindow(windowDimensions[0], windowDimensions[1], "Bash Gamez");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png"); // Creating map texture
    Vector2 mapPos{0.0, 0.0};                                   // screenPos, worldPos, mapPos

    const float mapScale = 4.0f;

    Character knight{windowDimensions[0], windowDimensions[1]}; // instance of the "Character" class called "knight"
    // knight.setScreenPos(windowDimensions[0], windowDimensions[1]);

    Prop props[2]{// Instance of the "Prop" class
                  Prop{Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
                  Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin{// Instance of the "Enemy" class

                 Vector2{800.f, 300.f},
                 LoadTexture("characters/goblin_idle_spritesheet.png"),

                 LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f); // Moving the map and the not the worldPos

        // Drawing map texture
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE); // scaling the map by a factor of 4

        // draw props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive()) // Character is not alive
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());

        // Map Bounds
        if (knight.getWorldPos().x < 0.0f ||
            knight.getWorldPos().y < 0.0f ||
            knight.getWorldPos().x + windowDimensions[0] > map.width * mapScale ||
            knight.getWorldPos().y + windowDimensions[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // Check Prop Collisions
        for (auto prop : props)
        {

            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.GetCollisionRec()))
            {

                knight.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }

        }

        // Game Logic Ends
        EndDrawing();
    }
}