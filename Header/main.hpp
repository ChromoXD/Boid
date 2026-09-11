#pragma once
#include <raylib.h>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 800;


struct Boid_Particles{
    float Vision_Radius;
    float Direction;
    float Velocity;
    float Position[2];
};

class Game{    
    public:
        std::vector<Boid_Particles> boids{};
        
        Game(int fps, int NOP){
            SetTargetFPS(fps);
            InitBoidParticle(NOP);
        }

        void InitBoidParticle(int NOP);
};
