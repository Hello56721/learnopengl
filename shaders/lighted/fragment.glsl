#version 330 core
out vec4 outColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPosition;

uniform vec3 viewPosition;

in vec3 normal;
in vec3 fragmentPosition;

float specularStrength = 0.5;

vec3 normalizedNormal = normalize(normal);
vec3 lightDirection = normalize(lightPosition - fragmentPosition);

vec3 calculateAmbient()
{
    float ambientStrength = 0.1;
    return ambientStrength * objectColor;
}

vec3 calculateDiffuse()
{
    float diffuseValue = max(dot(normalizedNormal, lightDirection), 0.0);
    return diffuseValue * lightColor;
}

vec3 calculateSpecular()
{
    vec3 viewDirection = normalize(viewPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normalizedNormal);
    
    float specularValue = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    return specularValue * specularStrength * objectColor;
}

void main()
{
    vec3 ambient = calculateAmbient();
    vec3 diffuse = calculateDiffuse();
    vec3 specular = calculateSpecular();
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    outColor = vec4(result, 1.0);
}