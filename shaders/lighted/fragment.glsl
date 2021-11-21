#version 330 core
out vec4 outColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPosition;

in vec3 normal;
in vec3 fragmentPosition;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * objectColor;
    
    vec3 normalizedNormal = normalize(normal);
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);
    
    float diffuseValue = max(dot(normalizedNormal, lightDirection), 0.0);
    vec3 diffuse = diffuseValue * lightColor;
    
    vec3 result = (ambient + diffuse) * objectColor;
    outColor = vec4(result, 1.0);
}