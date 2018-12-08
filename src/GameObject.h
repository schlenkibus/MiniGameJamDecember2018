#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class GameObject {
public:
    GameObject() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual bool onEvent(sf::Event& event);

protected:
    virtual void onResize(sf::Event& resizeEvent);
    const sf::Vector2f getViewSize() const;
};
