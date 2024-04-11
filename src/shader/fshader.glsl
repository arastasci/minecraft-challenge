#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture0;

void main()
{
    // FragColor = vec4(0.07f, 0.81f, 0.29f, 1.0);
    FragColor = texture(texture0, TexCoords);
}