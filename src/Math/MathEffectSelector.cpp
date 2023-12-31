#include <Math/MathEffectSelector.hpp>

std::vector<EffectFunction> MathEffectSelector::_functions =
{
    MathEffect::Wave,
    MathEffect::MultiWave,
    MathEffect::Ripple
};

EffectFunction MathEffectSelector::getFunction(MathEffects effect)
{
    return _functions[static_cast<int>(effect)];
}

MathEffects MathEffectSelector::getNextFunctionName(MathEffects effect)
{
    const auto effectId = static_cast<int>(effect);
    return static_cast<MathEffects>(effectId < _functions.size() - 1 ? effectId + 1 : 0);
}
