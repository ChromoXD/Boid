#pragma once
#include <raylib.h>
#include <bits/stdc++.h>

const float screenWidth = 1200;
const float screenHeight = 800;


struct Boid_Particles{
    float Vision_Radius;
    float Velocity;
    float Direction;
    float Position[2];
};

class Game{
    public:

    Game(int fps){
        SetTargetFPS(fps);
    }
};