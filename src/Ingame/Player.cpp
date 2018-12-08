#include <Box2D/Box2D.h>
#include "Player.h"

Player::Player(sf::Vector2f pos, b2World *world) : m_world(world) {
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
    m_body->SetFixedRotation(true);
    m_sprite.setSize(sf::Vector2f(20, 20));
    m_sprite.setOrigin(10, 10);
    auto po = m_body->GetTransform().p;
    m_sprite.setPosition(sf::Vector2f(po.x, po.y));
    m_sprite.setFillColor(sf::Color::Green);
    m_sprite.setRotation((int)(m_body->GetAngle() / 57.29578f) % 360);
    m_body->SetGravityScale(5);
}

void Player::update(float delta) {
    movement.update(delta);
    m_body->SetLinearVelocity(b2Vec2(movement.xSpeed, m_body->GetLinearVelocity().y));

    if(movement.up) {
        m_body->ApplyLinearImpulse(b2Vec2(0, -28000), m_body->GetTransform().p, true);
        movement.up = false;
    }

    const auto po = m_body->GetTransform().p;
    m_sprite.setPosition(sf::Vector2f(po.x, po.y));
}

bool Player::onEvent(sf::Event &e) {

    auto pressed = e.type == e.KeyPressed;
    auto released = e.type == e.KeyReleased;
    if(pressed || released) {
        switch(e.key.code) {
            case sf::Keyboard::Left:
                movement.left = pressed;
                break;
            case sf::Keyboard::Right:
                movement.right = pressed;
                break;
            case sf::Keyboard::Space:

                movement.up = pressed;
                if(pressed) {
                    static auto lastJump = sf::Clock();
                    if(lastJump.getElapsedTime().asSeconds() < 2) {
                        movement.up = false;
                    } else {
                        lastJump.restart();
                    }
                }
                break;
            default:
                break;
        }
    }
    return GameObject::onEvent(e);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(m_sprite);
}

const sf::Vector2f Player::getPosition() const {
    return m_sprite.getPosition();
}
