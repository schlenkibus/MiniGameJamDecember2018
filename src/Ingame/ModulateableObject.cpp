#include <iostream>
#include "ModulateableObject.h"
#include "LevelObject.h"

ModulateableObject::ModulateableObject(LevelObject* parent, b2World *world, sf::Vector2f pos, sf::Vector2f size) : m_world(world) {
    m_attributes["x"] = std::to_string((int)pos.x);
    m_attributes["y"] = std::to_string((int)pos.y);
    m_attributes["w"] = std::to_string((int)size.x);
    m_attributes["h"] = std::to_string((int)size.y);
    m_attributes["pysics"] = "true";
    m_parent = parent;
    init();
}

void ModulateableObject::update(float delta) {
    auto pos = m_body->GetTransform().p;
    m_drawShape.setPosition(sf::Vector2f(pos.x, pos.y));
    m_drawShape.setRotation((int)(m_body->GetAngle() * 57.29578f));
}

bool ModulateableObject::onEvent(sf::Event &e) {
    if(e.KeyReleased) {
        if(e.key.code == sf::Keyboard::G) {
            static sf::Clock t;
            if(t.getElapsedTime().asSeconds() > 1) {
                m_parent->openAttributesEditor(getAttributes(), [this](tAttributes newAttributes) {
                    setAttributes(newAttributes);
                });
                t.restart();
            }

        }
    }
    return GameObject::onEvent(e);
}

void ModulateableObject::draw(sf::RenderWindow &window) {
    window.draw(m_drawShape);
}

const ModulateableObject::tAttributes &ModulateableObject::getAttributes() {
    m_attributes["x"] = std::to_string((int)m_body->GetTransform().p.x);
    m_attributes["y"] = std::to_string((int)m_body->GetTransform().p.y);
    return m_attributes;
}

void ModulateableObject::init() {
    auto x = std::stoi(m_attributes["x"]);
    auto y = std::stoi(m_attributes["y"]);
    auto w = std::stoi(m_attributes["w"]);
    auto h = std::stoi(m_attributes["h"]);
    auto pysics = m_attributes["pysics"] == "true";

    auto oldAngle = m_body != nullptr ? m_body->GetAngle() : 0;

    b2BodyDef def;
    def.type = b2_dynamicBody;
    m_body = m_world->CreateBody(&def);
    m_shape.SetAsBox(w / 2, h / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_shape;
    fixtureDef.density = 1;
    m_fixture = m_body->CreateFixture(&fixtureDef);
    m_body->SetTransform(b2Vec2(x, y), oldAngle);
    m_body->SetBullet(true);
    m_drawShape.setSize(sf::Vector2f(w, h));
    m_drawShape.setOrigin(w / 2, h / 2);
    auto po = m_body->GetTransform().p;
    m_drawShape.setPosition(sf::Vector2f(po.x, po.y));
    m_drawShape.setRotation((int)(m_body->GetAngle() / 57.29578f) % 360);
    m_body->SetType(pysics ? b2_dynamicBody : b2_staticBody);
}

void ModulateableObject::setAttributes(const ModulateableObject::tAttributes &attributes) {
    m_attributes["x"] = std::to_string((int)m_body->GetTransform().p.x);
    m_attributes["y"] = std::to_string((int)m_body->GetTransform().p.y);

    for(const auto&[key, oldValue]: m_attributes) {
        const auto &newValue = attributes.at(key);
        if(oldValue != newValue) {
            if(key == "w" || key == "h") {
                try {
                    auto w = std::stoi(attributes.at("w"));
                    auto h = std::stoi(attributes.at("h"));
                    if(m_body != nullptr && m_fixture != nullptr)
                        m_body->DestroyFixture(m_fixture);
                    m_shape.SetAsBox(w / 2, h / 2);
                    b2FixtureDef fixtureDef;
                    fixtureDef.shape = &m_shape;
                    fixtureDef.density = 1;
                    m_body->CreateFixture(&fixtureDef);
                    m_drawShape.setSize(sf::Vector2f(w, h));
                    m_drawShape.setOrigin(w / 2, h / 2);
                    m_attributes["w"] = std::to_string((int)w);
                    m_attributes["h"] = std::to_string((int)h);
                } catch(...) {
                    std::cerr << "invalid argument probs\n";
                }
            } else if(key == "x" || key == "y") {
                try {
                    auto x = std::stoi(attributes.at("x"));
                    auto y = std::stoi(attributes.at("y"));
                    m_body->SetTransform(b2Vec2(x, y), m_body->GetAngle());
                    m_attributes["x"] = std::to_string((int)x);
                    m_attributes["y"] = std::to_string((int)y);
                } catch(...) {
                    std::cerr << "invalid argument probs\n";
                }
            } else if(key == "pysics") {
                m_body->SetType(newValue == "true" ? b2_dynamicBody : b2_staticBody);
                m_attributes[key] = newValue;
            }
        }
    }
    m_body->SetAwake(true);
}
