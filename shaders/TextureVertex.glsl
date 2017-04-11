#version 330 core

uniform mat4 MVP;                   //MVP passed from app

layout (location=0)in vec3 inVert;  // first attribute the vertex values from our VAO
layout (location=1)in vec2 inUV;    // second attribute the UV values from our VAO

out vec2 vertUV;                    // texcoord


void main()
{
    // pre-calculate for speed we will use this a lot

    // calculate the vertex position
    gl_Position = MVP*vec4(inVert, 1.0);

    // pass the UV values to the frag shader
    vertUV = inUV.st;
}
