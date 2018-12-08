#include <Box2D/Box2D.h>
#include <iostream>
#include "TestObject.h"

TestObject::TestObject(b2World *world, sf::Vector2f pos) : m_world(world) {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    m_body = m_world->CreateBody(&def);
    m_shape.SetAsBox(10, 10);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_shape;
    fixtureDef.density = 1;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetTransform(b2Vec2(pos.x, pos.y), 0);
    m_body->SetBullet(true);
    m_drawShape.setSize(sf::Vector2f(20, 20));
    m_drawShape.setOrigin(10, 10);
    auto po = m_body->GetTransform().p;
    m_drawShape.setPosition(sf::Vector2f(po.x, po.y));
    m_drawShape.setRotation((int)(m_body->GetAngle() / 57.29578f) % 360);
}

void TestObject::update(float delta) {
    auto pos = m_body->GetTransform().p;
    m_drawShape.setPosition(sf::Vector2f(pos.x, pos.y));
    m_drawShape.setRotation((int)(m_body->GetAngle() * 57.29578f));
}

bool TestObject::onEvent(sf::Event &e) {
    return GameObject::onEvent(e);
}

void TestObject::draw(sf::RenderWindow &window) {
    window.draw(m_drawShape);
}

void TestObject::onResize(sf::Event &resizeEvent) {

}
