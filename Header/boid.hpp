#pragma once
#include <vector>
#include "main.hpp"
#include <array>

int RandomFactor();

class BoidParticleClass{
    private:
        int NumberOfPaticles;

    public:

        int GetNumberOfParticles(){return this->NumberOfPaticles;}
        
        std::vector<float> Angle; 
        std::vector<Boid_Particles> boids;

        BoidParticleClass(int NOP){
            this->NumberOfPaticles = NOP;
            InitBoidParticle(NOP);
        }
    
    void InitBoidParticle(int NOP);
};

void ForceCalculation(BoidParticleClass * Boid);