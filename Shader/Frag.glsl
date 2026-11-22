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
    float aspect = u_resolution.x/u_resolution.y;
    vec2 uv = (gl_FragCoord.xy/u_resolution.y);

    for(int i = 0; i < Number; i++){
        float x = (uv.x - Particle_Array[i].Position[0]);
        float y = (uv.y - Particle_Array[i].Position[1]);

        if(i == Number-1){
            if(x*x + y*y < (radius + 0.005)*(radius + 0.002)){
                FragColor = vec4(1.0, 0.443, 0.443, 1.0);
                break;
            }
        }
        else{
            if(x*x + y*y < radius*radius){
                FragColor = vec4(1.0, 1.0, 1.0, 1.0);
                break;
            }
        }
        
    }
}