#include <iostream>
#include "Header/main.hpp"
#include "raylib.h"
#include <vector>
#include <glad.h>


void Game::InitBoidParticle(int size){
        for (size_t i = 0; i < size; i++) 
        {
            boids.push_back({0, 0, 0, {(float)(GetRandomValue(0, 800)/800.0), (float)(GetRandomValue(0, 800)/800.0)}});
            std::cout << boids[i].Position[0] << ", " << boids[i].Position[0] << std::endl;
        }

}

Game game(60, 12);


int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Shader FragShad = LoadShader(0, "Shaders/Frag.glsl");

    RenderTexture2D Screen = LoadRenderTexture(screenWidth, screenHeight);

    GLuint Boid_Position;
    glGenBuffers(1, &Boid_Position);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, Boid_Position);
    glBufferData(GL_SHADER_STORAGE_BUFFER,
            game.boids.size() * sizeof(game.boids[0]),
            game.boids.data(),
            GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, Boid_Position);

    while (!WindowShouldClose())
    {
        BeginTextureMode(Screen);
            ClearBackground((Color){ 15, 14, 18, 255 });
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        EndTextureMode();
            
            
        BeginDrawing();
        
            BeginShaderMode(FragShad);
                ClearBackground((Color){ 15, 14, 18, 255 });
                DrawTextureEx(Screen.texture, (Vector2){ 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
            EndShaderMode();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}