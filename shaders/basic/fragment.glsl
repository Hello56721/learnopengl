#version 330 core
out vec4 color;

uniform sampler2D texture1;

in vec2 textureCoordinates;

void main() {
    color = texture(texture1, textureCoordinates);
}