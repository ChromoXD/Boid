#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
#include <cmath>
#include "Header/boid.hpp"
#include "Header/main.hpp"

int RandomFactor()
{
    std::time_t now{std::time(nullptr)};
    std::tm *localTIme{std::localtime(&now)};
    int hour{localTIme->tm_hour};
    int min{localTIme->tm_min};
    int sec{localTIme->tm_sec};

    int factor{hour + min + sec};

    return factor;
}

void BoidParticleClass::InitBoidParticle(int size)
{

    int RF{RandomFactor()};

    for (size_t i{0}; i < size; i++)
    {
        int max_pos = (GetScreenWidth() - 1);

        boids.push_back({0.02,
                         (float)(GetRandomValue(100, (600 + RF)) / 100000.0),
                         (float)(GetRandomValue(0, 360) / 360.0),
                         {(float)(GetRandomValue(0, max_pos + RF) / ((float)max_pos + RF)),
                          (float)(GetRandomValue(0, max_pos + RF) / ((float)max_pos + RF))}});
        std::cout << boids[i].Direction << std::endl;
    }
}

void BoidParticleClass::AddForce(int index, float angle, float Newton, float repulsive_Force, float repulsive_Force_Angle, float Stearing_Angle)
{

    if (boids[index].Position[0] < 0.0f)
        boids[index].Position[0] += 1.0f;
    if (boids[index].Position[0] > 1.0f)
        boids[index].Position[0] -= 1.0f;
    if (boids[index].Position[1] < 0.0f)
        boids[index].Position[1] += 1.0f;
    if (boids[index].Position[1] > 1.0f)
        boids[index].Position[1] -= 1.0f;


    float Vx = cos(angle - Stearing_Angle*10) * Newton;
    float Vy = sin(angle - Stearing_Angle*10) * Newton;

    float Fx0 = cos(repulsive_Force_Angle) * repulsive_Force + Vx;
    float Fy0 = sin(repulsive_Force_Angle) * repulsive_Force + Vy;

    boids[index].Position[0] += (Fx0);
    boids[index].Position[1] += (Fy0);
}

std::pair<float, float> Saperation_And_Alignment_Force(float *NetAngle, Boid_Particles *boid, BoidParticleClass *N_boid)
{
    //seperation variables
    *NetAngle = 0;
    int NOP{N_boid->GetNumberOfParticles()};
    float Seperation_Force{0.0f},
          Angle[2]{0.0f, 0.0f},
          SI{3.0};


    // Alignment variables
    float Avg_vel[3]{0.0f, 0.0f, 0.0f};
    

    for (int i = 0; i < NOP; i++)
    {
        //varable calculations
        if (boid == &N_boid->boids[i]) continue;
        float relx = (N_boid->boids[i].Position[0] - boid->Position[0]) * 800;
        float rely = (N_boid->boids[i].Position[1] - boid->Position[1]) * 800;

        float r_dist = sqrtf(relx*relx + rely*rely);

        //aligment
        if (r_dist < 600)
        {
            Avg_vel[0] += cos(2*PI*N_boid->boids[i].Direction);
            Avg_vel[1] += sin(2*PI*N_boid->boids[i].Direction);
        }
        

        //seperation
        if (r_dist > 40.0f || r_dist == 0.0f) continue;

        float strength = SI / r_dist;
        Angle[0] -= relx * strength;
        Angle[1] -= rely * strength;
        Seperation_Force += strength;
    }

    //seperation
    if (NOP > 0)
        Seperation_Force /= NOP;
    *NetAngle = atan2f(Angle[1], Angle[0]);
        
    //aligment
    // Avg_vel[2] = sqrt(Avg_vel[0]*Avg_vel[0] + Avg_vel[1]*Avg_vel[1])/NOP;
    Avg_vel[2] = atan2(Avg_vel[1]/NOP, Avg_vel[0/NOP])/(2*PI);

    return {Seperation_Force, Avg_vel[2] - boid->Direction};
}

void ForceCalculation(BoidParticleClass *Boid)
{
    for (size_t i = 0; i < Boid->GetNumberOfParticles(); i++)
    {
        float NetAngle{0.0};
        float Angle{Boid->boids[i].Direction * 2 * PI};
        std::pair<float, float> SF{Saperation_And_Alignment_Force(&NetAngle, &Boid->boids[i], Boid)};

        Boid->AddForce(i, Angle, Boid->boids[i].Velocity, SF.first, NetAngle, SF.second);
    }
}
