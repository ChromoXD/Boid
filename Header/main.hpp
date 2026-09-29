#pragma once
#include <raylib.h>
#include <bits/stdc++.h>

const int screenWidth = 1200;
const int screenHeight = 800;


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