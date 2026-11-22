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

    // void AddForce(int index, float angle, float Newton);
    void AddForce(int index, float angle, float Newton, float repulsive_Force, float repulsive_Force_Angle, float Stearing_Angle);

};

void ForceCalculation(BoidParticleClass * Boid);