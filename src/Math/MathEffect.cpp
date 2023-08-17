#include <Math/MathEffect.hpp>

#include <glm/common.hpp>
#include <glm/exponential.hpp>

glm::vec3 MathEffect::Wave(float x, float z, float time)
{
    return glm::vec3(x, 0.2f * glm::sin(4.0f * PI * (x + z + time)), z);
}

glm::vec3 MathEffect::MultiWave(float x, float z, float time)
{
    glm::vec3 vec(x, glm::sin(PI * (x + 0.5f * time)), z);
    vec.y += 0.5f * glm::sin(2.0f * PI * (x + time));
    vec.y += glm::sin(PI * (x + z + 0.25f * time));
    vec.y *= 1.0f / 2.5f;

    return vec;
}

glm::vec3 MathEffect::Ripple(float x, float z, float time)
{
    float distance = glm::sqrt(x * x + z * z);

    glm::vec3 vec(x, glm::sin(PI * (4.0f * distance - time)), z);
    vec.y /= 1.0f + 10.0f * distance;

    return vec;
}

glm::vec3 MathEffect::Morph(float x, float z, float time, EffectFunction from, EffectFunction to, float progress)
{
    return glm::mix(from(x, z, time), to(x, z, time), glm::smoothstep(0.0f, 1.0f, progress));
}
