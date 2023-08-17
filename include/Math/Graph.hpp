#pragma once

#include <Math/MathEffectSelector.hpp>

#include <glm/ext/matrix_transform.hpp>

class Graph
{
    using ModelMatrices = std::vector<glm::mat4>;

private:
    void startTransition();
    void updateTransition();
    void updateEffect();

    void updateModelMatrix(EffectFunction from, EffectFunction to, float progress);
    void updateModelMatrix(EffectFunction effect);
    void updateMatrixAt(int index, const glm::vec3& position);

    float normalizeCoord(int axisValue) const;

public:
    explicit Graph(ModelMatrices* modelMatrices);
    void update(float deltaTime);
    int getGraphResolution() const;

private:
    ModelMatrices* _modelMatrices;

    const int _cubesPerAxes { 50 };
    const int _cubesPerGraph { _cubesPerAxes * _cubesPerAxes };

    const float _step { 2.0f / _cubesPerAxes };
    const glm::vec3 _resolutionScale = glm::vec3(1.0f, 1.0f, 1.0f) * _step;

    float _effectDuration { 2.0f };
    float _transitionDuration { 1.0f };
    bool _inTransition { false };
    float _duration { 0.0f };
    float _elapsedTime { 0.0f };

    MathEffects _currentFunction { MathEffects::Wave };
    MathEffects _transitionFunction { MathEffects::Ripple };

    static constexpr glm::mat4 _identityMatrix = glm::mat4(1.0f);
};