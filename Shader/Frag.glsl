#version 430 core

in vec2 fragTexCoord;

struct Boid {
    float Vision_Radius;
    float Velocity;
    float Direction;
    float Position[2];
};

uniform vec2 u_resolution;
uniform int Number;

layout(std430, binding = 1) buffer particles
{
    Boid Particle_Array[];
};

out vec4 FragColor;

float radius = 0.005;
float PI = 3.141593;
float a = 0.1;

void main(){
    FragColor = vec4(0.059, 0.055, 0.071, 1.0);
    vec2 localCord = fragTexCoord.xy/u_resolution;

    for(int i = 0; i < Number; i++){
        float x = fragTexCoord.x - Particle_Array[i].Position[0];
        float y = fragTexCoord.y - Particle_Array[i].Position[1];

        if(( x*x + y*y < radius*radius) || 
            (x*x + y*y < (Particle_Array[i].Vision_Radius*Particle_Array[i].Vision_Radius + 0.00001) && 
             x*x + y*y > (Particle_Array[i].Vision_Radius*Particle_Array[i].Vision_Radius - 0.00001))){
            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
            break;
        }
    }

}

//        float theta = Particle_Array[i].Direction * 2 * PI;
//
//        float x1 = (x-a/2)*cos(theta) - (y - a/(2*sqrt(3)))*sin(theta);
//        float y1 = (x-a/2)*cos(theta) - (y - a/(2*sqrt(3)))*cos(theta);
//
//        float x2 = (x+a/2)*cos(theta) - (y - a/(2*sqrt(3)))*sin(theta);                           
//        float y2 = (x+a/2)*cos(theta) - (y - a/(2*sqrt(3)))*cos(theta);
//        
//        float x3 = (x)*cos(theta) - (y - a/(sqrt(3)))*sin(theta);
//        float y3 = (x)*cos(theta) - (y - a/(sqrt(3)))*cos(theta);
//
//        if(x1*x1 + y1*y1 < radius*radius){
//            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
//            break;
//        }
//        if(x2*x2 + y2*y2 < radius*radius){
//            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
//            break;
//        }
//        if(x3*x3 + y3*y3 < radius*radius){
//            FragColor = vec4(1.0, 1.0, 1.0, 1.0);
//            break;
//        }