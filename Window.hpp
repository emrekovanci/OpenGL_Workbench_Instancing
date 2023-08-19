#pragma once

#include <SFML/Window.hpp>

#include <functional>
#include <vector>

// after window initialization
using InitCallback = std::function<void()>;

// every frame
using UpdateCallback = std::function<void(float)>;
using LifeTimeCallback = std::function<void(float)>;
using RenderCallback = std::function<void()>;

class Window
{
public:
    Window(unsigned int width, unsigned int height, const sf::String& title);
    void display();

    sf::Vector2i getMousePosition() const;
    sf::Vector2u getSize() const;
    float getAspectRatio() const;

    void addInitCallback(const InitCallback& callback);
    void addUpdateCallback(const UpdateCallback& callback);
    void addLifeTimeCallback(const LifeTimeCallback& callback);
    void addRenderCallback(const RenderCallback& callback);

private:
    sf::Window _window;
    sf::Event _event;

    std::vector<InitCallback> _initCallbacks;
    std::vector<UpdateCallback> _updateCallbacks;
    std::vector<LifeTimeCallback> _lifeTimeCallbacks;
    std::vector<RenderCallback> _renderCallbacks;

    // delta-time calculations
    sf::Clock _clock;
    float _previousTime { 0.0f };
    float _currentTime { 0.0f };

    // depth, stencil, antialiasing, majorVer, minorVer
    const sf::ContextSettings _context { 24, 8, 0, 3, 3 };
};