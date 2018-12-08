#pragma once

#include <Box2D/Box2D.h>
#include "../GameObject.h"
#include "ModulateableObject.h"

class ValueChangerProjectile : public GameObject {
public:
    explicit ValueChangerProjectile(b2World *world);
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void removeFromView();
    void shoot(sf::Vector2f pos, sf::Vector2f dir, int force);
    bool m_active = false;
protected:
    sf::RectangleShape m_drawShape;
    b2World* m_world;
    b2Body* m_body;
    b2PolygonShape m_shape;
};
