#pragma once

#include <SFML/System/Vector2.hpp>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "../../GameObject.h"
#include "../../DrawObjects/PolyShape.h"

class b2World;

class Tile : public GameObject {
public:
    Tile(b2World* world, sf::Vector2f pos);
    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;
protected:
    void onResize(sf::Event& resizeEvent) override;
    PolyShape shape;
    b2World* m_world;
    b2Body* m_body;
    b2PolygonShape m_shape;

    static const std::vector<sf::Vector2f> vertecies;
};
