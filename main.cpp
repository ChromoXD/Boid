#include <iostream>
#include "Header/main.hpp"
#include "raylib.h"
#include <vector>
#include <glad.h>
#include <array>
#include <cmath>

BoidParticleClass Boid(12);
Game game(60);

void BoidParticleClass::InitBoidParticle(int size){
    for (size_t i{0}; i < size; i++) 
    {
        boids.push_back({0, (float)GetRandomValue(0, 800), 0, {(float)(GetRandomValue(0, 799)/800.0), (float)(GetRandomValue(0, 799)/800.0)}});
        float OffsetX = (69069 * (int)boids[i].Direction + 5) % 1000000;
        float OffsetY = (69069 * (int)OffsetX + 5) % 1000000;
        Offsets.push_back({OffsetX, OffsetY});
        // std::cout << boids[i].Position[0] << ", " << boids[i].Position[0] << std::endl;
    }
}

void BoidParticleClass::AddForce(int index, float angle, float Newton){
    
    boids[index].Position[0] += cos(angle) * Newton;
    boids[index].Position[1] += sin(angle) * Newton;


    if (boids[index].Position[0] < 0.0f)
        boids[index].Position[0] += 1.0f;

    if (boids[index].Position[0] >= 1.0f)
        boids[index].Position[0] -= 1.0f;

    if (boids[index].Position[1] < 0.0f)
        boids[index].Position[1] += 1.0f;

    if (boids[index].Position[1] >= 1.0f)
        boids[index].Position[1] -= 1.0f;
    
}

void ForceCalculation(float Force){

    int OffsetX = 0;
    int OffsetY = 0;
    
    Image PerImg = GenImagePerlinNoise(100, 100, OffsetX + 100, OffsetY + 100, 1);
    
    for (size_t i = 0; i < Boid.GetNumberOfParticles(); i++)
    {
        OffsetX = static_cast<int>(Boid.Offsets[i][0]);
        OffsetY = static_cast<int>(Boid.Offsets[i][1]);
        PerImg = GenImagePerlinNoise(100, 100, OffsetX, OffsetY, 2.0);

        Color *pixel = LoadImageColors(PerImg);

        int x = (int)(Boid.boids[i].Position[0] * 100.0);
        int y = (int)(Boid.boids[i].Position[1] * 100.0);
        int index = y*100 + x;

        float noiseValue = pixel[index].r/255.0;

        float Angle = noiseValue * 2 * PI;

        Boid.AddForce(i, Angle, Force);

        UnloadImageColors(pixel);
        UnloadImage(PerImg);
    }
    
    
}


int main(void)
{

    InitWindow(screenWidth, screenHeight, "Boidz");

    Shader FragShad = LoadShader(0, "Shader/Frag.glsl");

    // Image perlinImg = GenImagePerlinNoise()

    RenderTexture2D Screen = LoadRenderTexture(screenWidth, screenHeight);

    GLuint Boid_Position;
    glGenBuffers(1, &Boid_Position);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, Boid_Position);
    glBufferData(GL_SHADER_STORAGE_BUFFER,
            Boid.boids.size() * sizeof(Boid.boids[0]),
            Boid.boids.data(),
            GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, Boid_Position);

    int ResolutionLoc = GetShaderLocation(FragShad, "u_resolution");
    int NumberLoc = GetShaderLocation(FragShad, "Number");
    int res[2] = {screenWidth, screenHeight};
    int NOP = Boid.GetNumberOfParticles();
    
    std::cout << NOP;

    while (!WindowShouldClose())
    {
        game.Time += 1;

        ForceCalculation(0.001);
        
        glBufferData(GL_SHADER_STORAGE_BUFFER,
                Boid.boids.size() * sizeof(Boid.boids[0]),
                Boid.boids.data(),
                GL_STATIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, Boid_Position);

        SetShaderValue(FragShad, ResolutionLoc, res, SHADER_UNIFORM_IVEC2 );
        SetShaderValue(FragShad, NumberLoc, &NOP, SHADER_UNIFORM_INT );
        
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