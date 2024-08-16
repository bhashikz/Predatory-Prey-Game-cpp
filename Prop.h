#include "raylib.h"

class Prop{
    public:
    Prop(Vector2 pos, Texture2D tex); // Constructor with input parameters
    void Render(Vector2 knightPos);   // Render function 
    Rectangle getCollisionRec(Vector2 knightPos);
    
    private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale = 4.0f;

};