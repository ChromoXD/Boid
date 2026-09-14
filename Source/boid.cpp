#include <iostream>
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
        boids.push_back({
            0.03,
            (float)(GetRandomValue(100, (100 + RF)) / 100000.0), 
            (float)(GetRandomValue(0, 360)/360.0),
            {
                (float)(GetRandomValue(0, 799 + RF) / (800.0 + RF)), 
                (float)(GetRandomValue(0, 799 + RF) / (800.0 + RF))
            }
        });
        std::cout << boids[i].Direction << std::endl;
    }
}

void BoidParticleClass::AddForce(int index, float angle, float Newton)
{

    boids[index].Position[0] += cos(angle) * Newton;
    boids[index].Position[1] += sin(angle) * Newton;

    if (boids[index].Position[0] < 0.0f)
        boids[index].Position[0] += 1.0f;
    if (boids[index].Position[0] > 1.0f)
        boids[index].Position[0] -= 1.0f;
    if (boids[index].Position[1] < 0.0f)
        boids[index].Position[1] += 1.0f;
    if (boids[index].Position[1] > 1.0f)
        boids[index].Position[1] -= 1.0f;
}

void ForceCalculation(BoidParticleClass * Boid)
{

    int OffsetX{100};
    int OffsetY{100};

    Image PerImg{GenImagePerlinNoise(200, 200, OffsetX, OffsetY, 2)};
    Color *pixel{LoadImageColors(PerImg)};

    for (size_t i = 0; i < Boid->GetNumberOfParticles(); i++)
    {   
        float Angle{Boid->boids[i].Direction * 2 * PI};
        Boid->AddForce(i, Angle, Boid->boids[i].Velocity);
    }
    
    UnloadImageColors(pixel);
    UnloadImage(PerImg);
}
