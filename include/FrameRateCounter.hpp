#pragma once

#include <limits>
#include <string>

class FrameRateCounter
{
public:
    enum class Display { FPS, MS };

public:
    FrameRateCounter() = default;
    FrameRateCounter(Display displayMode = Display::FPS, float sampleDuration = 1.0f);

    void update(float deltaTime);

    std::string getUnit() const;
    float getValue() const;

private:
    Display _displayMode { Display::FPS };
    float _sampleDuration { 1.0f };

    int _frames { 0 };
    float _duration { 0.0f };

    float _value {};
};