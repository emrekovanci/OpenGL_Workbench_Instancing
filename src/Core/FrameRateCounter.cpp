#include <Core/FrameRateCounter.hpp>

FrameRateCounter::FrameRateCounter(Display displayMode, float sampleDuration) :
    _sampleDuration { sampleDuration },
    _displayMode { displayMode }
{

}

void FrameRateCounter::update(float deltaTime)
{
    _frames += 1;
    _duration += deltaTime;

    if (_duration >= _sampleDuration)
    {
        _value = (_displayMode == Display::FPS)
            ? _frames / _duration
            : 1000.0f * _duration / _frames;

        _frames = 0;
        _duration = 0.0f;
    }
}

std::string FrameRateCounter::getUnit() const
{
    return (_displayMode == Display::FPS) ? "FPS" : "MS";
}

float FrameRateCounter::getValue() const
{
    return _value;
}
