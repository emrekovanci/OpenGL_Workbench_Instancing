#pragma once

#include <functional>

#include <glm/trigonometric.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/vec3.hpp>

enum class MathEffects
{
    Wave = 0,
    MultiWave,
    Ripple
};

using EffectFunction = std::function<glm::vec3(float, float, float)>;

struct MathEffect
{
    static glm::vec3 Wave(float x, float z, float time);
    static glm::vec3 MultiWave(float x, float z, float time);
    static glm::vec3 Ripple(float x, float z, float time);
    static glm::vec3 Morph(float x, float z, float time, EffectFunction from, EffectFunction to, float progress);

    constexpr static float PI = glm::pi<float>();
};