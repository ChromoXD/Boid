#include <iostream>
#include "Header/main.hpp"
#include "Header/boid.hpp"
#include "raylib.h"
#include <vector>
#include <glad.h>
#include <array>
#include <cmath>
#include <ctime>

BoidParticleClass Boid(100);
Game game(60);

void Update();

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Boidz");

    Shader FragShad{LoadShader(0, "Shader/Frag.glsl")};
    RenderTexture2D Screen{LoadRenderTexture(screenWidth, screenHeight)};

    GLuint Boid_Position;
    glGenBuffers(1, &Boid_Position);
    glBindBuffer(
        GL_SHADER_STORAGE_BUFFER, 
        Boid_Position);
    glBufferData(
        GL_SHADER_STORAGE_BUFFER, 
        Boid.boids.size() * sizeof(Boid.boids[0]), 
        Boid.boids.data(), 
        GL_STATIC_DRAW);
    glBindBufferBase(
        GL_SHADER_STORAGE_BUFFER, 
        1, 
        Boid_Position);

    int ResolutionLoc{GetShaderLocation(FragShad, "u_resolution")}, 
        NumberLoc{GetShaderLocation(FragShad, "Number")}, 
        res[2]{screenWidth, screenHeight}, 
        NOP{Boid.GetNumberOfParticles()};

    while (!WindowShouldClose())
    {

        Update();

        glBufferData(GL_SHADER_STORAGE_BUFFER, 
            Boid.boids.size() * sizeof(Boid.boids[0]), 
            Boid.boids.data(), 
            GL_STATIC_DRAW
        );
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, Boid_Position);

        SetShaderValue(FragShad, ResolutionLoc, res, SHADER_UNIFORM_IVEC2);
        SetShaderValue(FragShad, NumberLoc, &NOP, SHADER_UNIFORM_INT);

        BeginTextureMode(Screen);
        ClearBackground((Color){15, 14, 18, 255});
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        EndTextureMode();

        BeginDrawing();
        BeginShaderMode(FragShad);
        ClearBackground((Color){15, 14, 18, 255});
        DrawTextureEx(Screen.texture, (Vector2){0.0f, 0.0f}, 0.0f, 1.0f, WHITE);
        EndShaderMode();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


void Update(){
        ForceCalculation(&Boid);
}