#version 430 core

in vec2 fragTexCoord;

struct Boid {
    float Vision_Radius;
    float Direction;
    float Velocity;
    float Position[2];
};

layout(std430, binding = 1) buffer particles
{
    Boid Particle_Array[];
};

out vec4 FragColor;

float radius = 0.01;

void main(){
    FragColor = vec4(1.0, 0.055, 0.071, 1.0);

    //for(int i = 0; i < 10; i++){
    //    float x = fragTexCoord.x - Particle_Array[i].Position[0];
    //    float y = fragTexCoord.y - Particle_Array[i].Position[1];
//
    //    if(x*x + y*y < radius*radius){
    //        FragColor = vec4(0.369, 0.659, 0.902, 1.0);
    //        break;
    //    }
    //}

}