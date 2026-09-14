#pragma once
#include <vector>
#include "main.hpp"
#include <array>

int RandomFactor();

class BoidParticleClass{
    private:
        int NumberOfPaticles;

    public:

        std::vector<std::array<int, 2>> Offsets;

        std::vector<Boid_Particles> boids{};

        BoidParticleClass(int NOP){
            this->NumberOfPaticles = NOP;
            InitBoidParticle(NOP);
        }
    
    void InitBoidParticle(int NOP);

    void AddForce(int index, float angle, float Newton);

    int GetNumberOfParticles(){return this->NumberOfPaticles;}
};

void ForceCalculation(BoidParticleClass * Boid);