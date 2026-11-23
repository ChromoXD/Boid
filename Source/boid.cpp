#include <bits/stdc++.h>
#include <cmath>
#include <random>
#include "Header/boid.hpp"
#include "Header/main.hpp"


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1,199);

void BoidParticleClass::InitBoidParticle(int size)
{
    const float aspect = screenWidth / screenHeight;
    boids.clear();
    for (int i = 0; i < size; i++)
        boids.push_back({
            0.08f,
            GetRandomValue(300, 800) / 100000.0f,
            GetRandomValue(0, 359) / 360.0f,
            { GetRandomValue(0, 10000) / 10000.0f * aspect,
              GetRandomValue(0, 10000) / 10000.0f }
        });
}

void ForceCalculation(BoidParticleClass *B)
{
    auto &bs = B->boids;
    const int n = bs.size();
    std::vector<float> newDir(n);

    const float seperation_W = 1.0f;
    const float Alignment_W = 1.0f;
    const float cohision_W = 0.5f;
    const float turn = 0.1f;

    for (int i = 0; i < n; i++)
    {
        if (i == n-1) { newDir[n-1] = bs[n-1].Direction; continue; }
        const float tr = 0.0015f;
        float &bd = B->boids[n-1].Direction;

        if (IsKeyDown(KEY_LEFT))  bd += tr;
        if (IsKeyDown(KEY_RIGHT)) bd -= tr;
        if (bd < 0)  bd += 1.0f;
        if (bd >= 1) bd -= 1.0f;

        if (IsKeyDown(KEY_UP))   bs[n-1].Velocity = fminf(bs[n-1].Velocity + 0.00005f, 0.015f);
        if (IsKeyDown(KEY_DOWN)) bs[n-1].Velocity = fmaxf(bs[n-1].Velocity - 0.00005f, 0.001f);

        float th = bs[i].Direction * 2*PI;
        float hx = cosf(th), hy = sinf(th);

        float s[2]{0,0};
        float a[2]{0,0};
        float c[2]{0,0};
        
        int cnt = 0;
        float r = bs[i].Vision_Radius;
        
        float seperation_R = 0.3f * r;
        
        for (int j = 0; j < n; j++)
        {
            if (j == i && j == n-1) continue;
            float dx = bs[i].Position[0] - bs[j].Position[0];
            float dy = bs[i].Position[1] - bs[j].Position[1];
            float d2 = dx*dx + dy*dy;
            if (d2 > r*r || d2 < 1e-12f) continue;

            float d = sqrtf(d2);
            s[0] += (dx / d) * (1.0f - d / r);
            s[1] += (dy / d) * (1.0f - d / r);


            if (d < seperation_R)
            {
                float k = 1.0f - d / seperation_R;
                s[0] += (dx / d) * k * k;
                s[1] += (dy / d) * k * k;
            }

            float tj = bs[j].Direction * 2*PI;
            a[0] += cosf(tj);  
            a[1] += sinf(tj);
            c[0] += bs[j].Position[0];  
            c[1] += bs[j].Position[1];
            cnt++;
        }

        float f[2]{0,0};
        if (cnt > 0)
        {
            f[0] += seperation_W * s[0] + Alignment_W * (a[0] / cnt);
            f[1] += seperation_W * s[1] + Alignment_W * (a[1] / cnt);

            f[0] += cohision_W * (c[0] / cnt - bs[i].Position[0]);
            f[1] += cohision_W * (c[1] / cnt - bs[i].Position[1]);
        }

        float nx = hx + turn * f[0];
        float ny = hy + turn * f[1];
        newDir[i] = atan2f(ny, nx) / (2*PI);
        if (newDir[i] < 0) newDir[i] += 1.0f;
    }

    for (int i = 0; i < n; i++)
    {
        bs[i].Direction = newDir[i];
        float th = newDir[i] * 2*PI;
        bs[i].Position[0] += bs[i].Velocity * cosf(th);
        bs[i].Position[1] += bs[i].Velocity * sinf(th);

        float aspect = ((float)GetScreenWidth())/((float)GetScreenHeight());

        if (B->boids[i].Position[0] < 0)      B->boids[i].Position[0] += aspect;
        if (B->boids[i].Position[0] > aspect) B->boids[i].Position[0] -= aspect;
        if (B->boids[i].Position[1] < 0)      B->boids[i].Position[1] += 1.0f;
        if (B->boids[i].Position[1] > 1.0f)   B->boids[i].Position[1] -= 1.0f;
    }
}