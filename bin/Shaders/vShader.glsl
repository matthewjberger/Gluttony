#version 120

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoords;

varying vec2 TexCoords;

uniform mat4 mvpMatrix;

void main(void)
{
   gl_Position = mvpMatrix * vec4(position, 1.0);
   TexCoords = texCoords;
}

