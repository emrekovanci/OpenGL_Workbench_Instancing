#include "Window.hpp"

#include <glad/glad.h>

Window::Window(unsigned int width, unsigned int height, const sf::String& title)
{
    _window.create(sf::VideoMode(width, height), title, sf::Style::Default, _context);
    _previousTime = _clock.getElapsedTime().asSeconds();

    for (const auto& initCallback : _initCallbacks)
    {
        initCallback();
    }
}

void Window::display()
{
    while (_window.isOpen())
    {
        while (_window.pollEvent(_event))
        {
            for (const auto& eventCallback : _eventCallbacks)
            {
                eventCallback(_event);
            }
        }

        _currentTime = _clock.getElapsedTime().asSeconds();
        const float deltaTime = _currentTime - _previousTime;
        _previousTime = _currentTime;

        for (const auto& updateCallback : _updateCallbacks) { updateCallback(deltaTime); }
        for (const auto& lifeTimeCallback : _lifeTimeCallbacks) { lifeTimeCallback(_currentTime); }
        for (const auto& renderCallback : _renderCallbacks) { renderCallback(); }

        _window.display();
    }
}

void Window::close()
{
    _window.close();
}

sf::Vector2i Window::getMousePosition() const
{
    return sf::Mouse::getPosition(_window);
}

sf::Vector2u Window::getSize() const
{
    return _window.getSize();
}

float Window::getAspectRatio() const
{
    return static_cast<float>(getSize().x) / getSize().y;
}

void Window::addInitCallback(const InitCallback& callback)
{
    _initCallbacks.push_back(callback);
}

void Window::addUpdateCallback(const UpdateCallback& callback)
{
    _updateCallbacks.push_back(callback);
}

void Window::addLifeTimeCallback(const LifeTimeCallback& callback)
{
    _lifeTimeCallbacks.push_back(callback);
}

void Window::addRenderCallback(const RenderCallback& callback)
{
    _renderCallbacks.push_back(callback);
}

void Window::addEventCallback(const EventCallback& callback)
{
    _eventCallbacks.push_back(callback);
}
