#include <memory>
#include <Box2D/Dynamics/b2Fixture.h>
#include <iostream>
#include "TerrainObject.h"
#include "../../Application.h"
#include "../../Tools/MathTools.h"

TerrainObject::TerrainObject(b2World* world, const std::vector<b2Vec2>& polygons) :
m_world(world), m_shape(), m_polys(convertToBox2DCoords(polygons)), m_drawObject(convertToSFMLCoords(polygons))
{
    calcObject();
}

void TerrainObject::draw(sf::RenderWindow &window) {
    m_drawObject.draw(window);
}

bool TerrainObject::onEvent(sf::Event &e) {
    return GameObject::onEvent(e);
}

void TerrainObject::update(float delta) {
    auto pos = m_body->GetTransform().p;
    m_drawObject.m_shape.setPosition(sf::Vector2f(pos.x, pos.y));
    m_drawObject.setRotation((int)(m_body->GetAngle()*180/M_1_PI) % 360);
}

void TerrainObject::onResize(sf::Event &resizeEvent) {
    GameObject::onResize(resizeEvent);
}

std::vector<sf::Vector2f> TerrainObject::convertToSFMLCoords(const std::vector<b2Vec2>& vector) {
    std::vector<sf::Vector2f> ret;
    ret.reserve(vector.size());

    for(auto& pos: vector) {
        ret.emplace_back(sf::Vector2f(pos.x, pos.y));
    }
    return ret;
}

std::vector<b2Vec2> TerrainObject::convertToBox2DCoords(const std::vector<b2Vec2> &vector) {
    std::vector<b2Vec2> ret;
    ret.reserve(vector.size());
    for(auto p: vector)
        ret.emplace_back(p);
    return ret;
}

bool contains(const sf::CircleShape* shape, float x, float y) {
    return shape->getRadius() >= MathTools::distance(shape->getPosition().x, shape->getPosition().y, x, y);
}

void TerrainObject::calcObject() {
    if(m_fixture)
        m_body->DestroyFixture(m_fixture);

    if(m_body)
        m_world->DestroyBody(m_body);

    m_shape = std::make_unique<b2ChainShape>();
    m_bodyDef.type = b2_staticBody;
    m_body = m_world->CreateBody(&m_bodyDef);
    m_shape->CreateLoop(&*m_polys.begin(), static_cast<int32>(m_polys.size()));
    m_fixtureDef.shape = m_shape.get();
    m_fixture = m_body->CreateFixture(&m_fixtureDef);
    auto po = m_body->GetTransform().p;
    m_drawObject.setPosition(sf::Vector2f(po.x, po.y));
}