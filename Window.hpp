#pragma once

#include <SFML/Window.hpp>

#include <functional>
#include <vector>

using InitCallback = std::function<void()>;
using UpdateCallback = std::function<void(float)>;
using LifeTimeCallback = std::function<void(float)>;
using RenderCallback = std::function<void()>;
using EventCallback = std::function<void(sf::Event)>;

class Window
{
public:
    Window(unsigned int width, unsigned int height, const sf::String& title);

    void display();
    void close();

    sf::Vector2i getMousePosition() const;
    sf::Vector2u getSize() const;
    float getAspectRatio() const;

    void addInitCallback(const InitCallback& callback);
    void addUpdateCallback(const UpdateCallback& callback);
    void addLifeTimeCallback(const LifeTimeCallback& callback);
    void addRenderCallback(const RenderCallback& callback);
    void addEventCallback(const EventCallback& callback);

private:
    sf::Window _window;
    sf::Event _event;

    // after window initialization
    std::vector<InitCallback> _initCallbacks;

    // every frame
    std::vector<UpdateCallback> _updateCallbacks;
    std::vector<LifeTimeCallback> _lifeTimeCallbacks;
    std::vector<RenderCallback> _renderCallbacks;

    // window events
    std::vector<EventCallback> _eventCallbacks;

    // delta-time calculations
    sf::Clock _clock;
    float _previousTime { 0.0f };
    float _currentTime { 0.0f };
};