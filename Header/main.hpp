#pragma once
#include <raylib.h>
#include <vector>
#include <array>

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
    int Time = 0;

    Game(int fps){
        SetTargetFPS(fps);
    }
};

class BoidParticleClass{
    private:
        int NumberOfPaticles;

    public:

        std::vector<std::array<float, 2>> Offsets;

        std::vector<Boid_Particles> boids{};

        BoidParticleClass(int NOP){
            this->NumberOfPaticles = NOP;
            InitBoidParticle(NOP);
        }
    
    void InitBoidParticle(int NOP);

    void AddForce(int index, float angle, float Newton);

    int GetNumberOfParticles(){return this->NumberOfPaticles;}
};