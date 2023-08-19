#include "Window.hpp"

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
            if (_event.type == sf::Event::Closed) { _window.close(); }
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

sf::Vector2u Window::getSize() const
{
    return _window.getSize();
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