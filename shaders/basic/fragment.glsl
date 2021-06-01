#version 330 core
out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 textureCoordinates;

void main() {
    color = mix(texture(texture1, textureCoordinates), texture(texture2, textureCoordinates), 0.2);
}