#include <iostream>
#include <bits/stdc++.h>
#include "Header/main.hpp"
#include "Header/boid.hpp"
#include "raylib.h"
#include <glad.h>
#include <cmath>
#include <ctime>

BoidParticleClass Boid(100);
Game game(24);

void Update();

int main(void)
{
    InitWindow(static_cast<int>(screenWidth), static_cast<int>(screenHeight), "Boidz");

    Shader FragShad{LoadShader(0, "Shader/Frag.glsl")};
    RenderTexture2D Screen{LoadRenderTexture(static_cast<int>(screenWidth), static_cast<int>(screenHeight))};

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
        NOP{Boid.GetNumberOfParticles()};
        
    float res[2]{screenWidth, screenHeight};
        
    while (!WindowShouldClose())
    {
        Update();

        glBufferData(GL_SHADER_STORAGE_BUFFER,
                     Boid.boids.size() * sizeof(Boid.boids[0]),
                     Boid.boids.data(),
                     GL_STATIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, Boid_Position);

        SetShaderValue(FragShad, ResolutionLoc, res, SHADER_UNIFORM_VEC2);
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

void Update()
{
    ForceCalculation(&Boid);
}


