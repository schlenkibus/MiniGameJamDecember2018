#pragma once

#include "../GameObject.h"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <unordered_map>

class LevelObject;

class ModulateableObject : public GameObject {
public:
    typedef std::unordered_map<std::string, std::string> tAttributes;
    ModulateableObject(LevelObject* parent, b2World* world, sf::Vector2f pos, sf::Vector2f size);
    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;
    const tAttributes& getAttributes();
    void setAttributes(const tAttributes& attributes);
protected:
    void init();
    tAttributes m_attributes;
    sf::RectangleShape m_drawShape;
    b2World* m_world = nullptr;
    b2Body* m_body = nullptr;
    b2Fixture* m_fixture = nullptr;
    b2PolygonShape m_shape;
    LevelObject* m_parent = nullptr;
};
