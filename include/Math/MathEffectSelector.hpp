#pragma once

#include <Math/MathEffect.hpp>

#include <functional>
#include <vector>

class MathEffectSelector
{
public:
    static EffectFunction getFunction(MathEffects effect);
    static MathEffects getNextFunctionName(MathEffects effect);

private:
    static std::vector<EffectFunction> _functions;
};