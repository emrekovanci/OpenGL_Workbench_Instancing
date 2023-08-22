#include <Math/Graph.hpp>

void Graph::startTransition()
{
    _inTransition = true;
    _transitionFunction = _currentFunction;
    _currentFunction = MathEffectSelector::getNextFunctionName(_currentFunction);
}

void Graph::updateTransition()
{
    EffectFunction from = MathEffectSelector::getFunction(_transitionFunction);
    EffectFunction to = MathEffectSelector::getFunction(_currentFunction);
    const float progress = _duration / _transitionDuration;

    updateTransforms(from, to, progress);
}

void Graph::updateEffect()
{
    EffectFunction effect = MathEffectSelector::getFunction(_currentFunction);

    updateTransforms(effect);
}

void Graph::updateTransforms(EffectFunction from, EffectFunction to, float progress)
{
    for (int i = 0, x = 0, z = 0; i < _cubesPerGraph; ++i, ++x)
    {
        if (x == _cubesPerAxes)
        {
            x = 0;
            z += 1;
        }

        const float xPos = normalizeCoord(x);
        const float zPos = normalizeCoord(z);
        const glm::vec3 position = MathEffect::Morph(xPos, zPos, _elapsedTime, from, to, progress);
        updateTransformAt(i, position);
    }
}

void Graph::updateTransforms(EffectFunction effect)
{
    for (int i = 0, x = 0, z = 0; i < _cubesPerGraph; ++i, ++x)
    {
        if (x == _cubesPerAxes)
        {
            x = 0;
            z += 1;
        }

        const float xPos = normalizeCoord(x);
        const float zPos = normalizeCoord(z);
        const glm::vec3 position = effect(xPos, zPos, _elapsedTime);
        updateTransformAt(i, position);
    }
}

void Graph::updateTransformAt(int index, const glm::vec3& position)
{
    Transform transform = glm::translate(_identityMatrix, position);
    transform = glm::scale(transform, _resolutionScale);
    (*_transforms)[index] = transform;
}

float Graph::normalizeCoord(int axisValue) const
{
    return (axisValue + 0.5f) * _step - 1.0f;
}

Graph::Graph(Transforms* transforms) : _transforms { transforms }
{
    _transforms->reserve(_cubesPerGraph);

    for (int i = 0; i < _cubesPerGraph; ++i)
    {
        _transforms->push_back(glm::mat4(1.0f));
    }
}

void Graph::update(float deltaTime)
{
    _elapsedTime += deltaTime;
    _duration += deltaTime;

    if (_inTransition)
    {
        if (_duration >= _transitionDuration)
        {
            _duration -= _transitionDuration;
            _inTransition = false;
        }
    }
    else if (_duration >= _effectDuration)
    {
        _duration -= _effectDuration;
        startTransition();
    }

    if (_inTransition)
    {
        updateTransition();
    }
    else
    {
        updateEffect();
    }
}

int Graph::getGraphResolution() const
{
    return _cubesPerGraph;
}
