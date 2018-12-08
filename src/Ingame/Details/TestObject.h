#pragma once

#include <Box2D/Dynamics/b2World.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../../GameObject.h"

class TestObject : public GameObject {
public:
    explicit TestObject(b2World* world, sf::Vector2f pos);
    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;
protected:
    void onResize(sf::Event& resizeEvent) override;
    sf::RectangleShape m_drawShape;
    b2World* m_world;
    b2Body* m_body;
    b2PolygonShape m_shape;
};

