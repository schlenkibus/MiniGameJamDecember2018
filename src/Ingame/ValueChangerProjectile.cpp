#include "ValueChangerProjectile.h"

ValueChangerProjectile::ValueChangerProjectile(b2World *world) {
    sf::Vector2f pos = {0, 0};

    m_world = world;
    b2BodyDef def;
    def.type = b2_dynamicBody;
    m_body = m_world->CreateBody(&def);
    m_shape.SetAsBox(10, 3);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_shape;
    fixtureDef.density = 1;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetTransform(b2Vec2(pos.x, pos.y), 0);
    m_body->SetBullet(true);
    m_body->SetUserData(this);
    m_drawShape.setSize(sf::Vector2f(20, 6));
    m_drawShape.setOrigin(5, 3);
    auto po = m_body->GetTransform().p;
    m_drawShape.setPosition(sf::Vector2f(po.x, po.y));
    m_drawShape.setRotation((int)(m_body->GetAngle() / 57.29578f) % 360);
}

void ValueChangerProjectile::draw(sf::RenderWindow &window) {
    if(m_active)
        window.draw(m_drawShape);
}

void ValueChangerProjectile::update(float deltaTime) {
    auto pos = m_body->GetTransform().p;
    m_drawShape.setPosition(sf::Vector2f(pos.x, pos.y));
    m_drawShape.setRotation((int)(m_body->GetAngle() * 57.29578f));
}

void ValueChangerProjectile::removeFromView() {
    //m_body->SetTransform(b2Vec2(-10000, -10000), 0);
    m_active = false;
}

void ValueChangerProjectile::shoot(sf::Vector2f pos, sf::Vector2f dir, int force) {
    m_active = true;
    force = force * 100;
    auto forceDir = pos - dir;
    forceDir.x = -forceDir.x;
    forceDir.y = -forceDir.y;
    m_body->SetLinearVelocity(b2Vec2(0,0));
    m_body->SetAngularVelocity(0);
    m_body->SetTransform(b2Vec2(pos.x, pos.y - 30), 0);
    m_body->ApplyForceToCenter(b2Vec2(forceDir.x * force, forceDir.y * force), true);
}
