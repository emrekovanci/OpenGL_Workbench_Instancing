#version 330 core

in vec4 WorldPosition;
in vec3 WorldNormal;

out vec4 FragmentColor;

uniform vec3 LightPosition;
uniform vec3 ViewPosition;

void main()
{
    vec3 normal = normalize(WorldNormal);
    vec3 lightDirection = normalize(LightPosition - WorldPosition.xyz);

    vec3 lightColor = vec3(1.0);

    // ambient
    vec3 ambient = lightColor * 0.2;

    // diffuse
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 1.0;
    vec3 viewDirection = normalize(ViewPosition - WorldPosition.xyz);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;

    // result
    vec3 albedo = clamp(WorldPosition.xyz * 0.5 + 0.5, 0.0, 1.0);
    vec3 color = albedo.xyz * (ambient + diffuse + specular);

    FragmentColor = vec4(color, 1.0);
}