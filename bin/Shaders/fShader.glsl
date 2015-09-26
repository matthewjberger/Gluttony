#version 120

varying vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main(void)
{
    gl_FragColor = vec4(texture2D(texture_diffuse1, TexCoords));
}

