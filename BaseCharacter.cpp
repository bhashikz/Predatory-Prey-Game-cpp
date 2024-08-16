#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(){

}
void BaseCharacter::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec(){
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width*scale,
        height*scale
    };
}

void BaseCharacter::tick(float deltaTime){

    worldPosLastFrame = worldPos;

    // Animation code to the tick function
    runningTime += deltaTime;
    if (runningTime >= updateTime){
        runningTime = 0;
        frame++;

        if (frame > maxFrame){
            frame = 0;
        }
    }

    if (Vector2Length(velocity) != 0.0){ // For non-zero length of direction vector
        // Moving position of character in the world 
        // set worldPos = worldPos + direction i.e. vector addition since we're changing character's world position
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));// functions in "raymath.h"
        velocity.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f; // Ternary operator 
        texture = run;
    }
    else{
            texture = idle;
    }
    velocity = {};



    // Creating source and destination rectangles/ Draw the character
    Rectangle knightSourceRec{ // Source rectangle is the rectangle from the spritesheet that we use
                              knightSourceRec.x = frame * width,
                              knightSourceRec.y = 0.0f,
                              knightSourceRec.width = rightLeft * width ,
                              knightSourceRec.height = height
                              };

    Rectangle knightDestRec{ // Destination rectangle is the position on the window where we draw the rectangle
                            knightDestRec.x = getScreenPos().x,
                            knightDestRec.y = getScreenPos().y,
                            knightDestRec.width = scale * width , // Scaling by a factor of 4
                            knightDestRec.height = scale * height
                            };

    // Drawing Source rectangles, source is a section in the sprite sheet
    DrawTexturePro(texture, knightSourceRec, knightDestRec, Vector2{}, 0.0f, WHITE);



}