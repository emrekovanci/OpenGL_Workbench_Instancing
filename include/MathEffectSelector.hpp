#pragma once

#include <functional>
#include <vector>

#include "MathEffect.hpp"

class MathEffectSelector
{
public:
    static EffectFunction getFunction(MathEffects effect);
    static MathEffects getNextFunctionName(MathEffects effect);

private:
    static std::vector<EffectFunction> _functions;
};