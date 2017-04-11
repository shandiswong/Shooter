#version 330 core

uniform sampler2D tex; // this is a pointer to the current 2D texture object

in vec2 vertUV; //texcoord from the vert shader

layout (location=0) out vec4 outColour;

void main ()
{
    // set the fragment colour to the current texture
    outColour = texture(tex,vertUV);
}
