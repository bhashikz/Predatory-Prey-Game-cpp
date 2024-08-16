#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter{

public:
    BaseCharacter();
    virtual void tick(float deltaTime);

    Vector2 getWorldPos(){  // Getter Method, with return type Vector2
        return worldPos;    // Accessor method, accesses value "worldpos" but prevents from changing.
    }
    // Class methods have access to class variables, even private ones!   
    void undoMovement();                 // Tick (Like a clock) Function Call
    Rectangle GetCollisionRec();
    virtual Vector2 getScreenPos() = 0;

    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }


protected:
    // Loading Textures
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")}; // Stationary knight spritesheet
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")}; // Stationary knight spritesheet
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};   // Moving knight spritesheet

    Vector2 screenPos{}; // Starting Position of the character on the screen/window (knightPos to screenPos)
    Vector2 worldPos{};  // Moving position of the character in the world
    Vector2 worldPosLastFrame{};

    // 1: facing right, -1: facing left
    float rightLeft = 1.0f;

    // Animation variables/ Member variables of the class "Character"
    float runningTime = 0;
    float updateTime = 1.0 / 12.0;
    int frame = 0;
    int maxFrame = 6;
    float speed = 4.0f;

    float width{}; 
    float height{};
    float scale = 4.0f;
    Vector2 velocity{};

private: 
    bool alive{true};


};

#endif