#include "Cake.h"
#include "LevelObject.h"
#include "Player.h"

Cake::Cake(LevelObject* parent, sf::Vector2f pos) : b(pos, "Next Level!", [&](sf::Event& e, Button& b) {
    if(b.isHighlighted()) {
        if(e.type == sf::Event::MouseButtonReleased) {
            if(e.mouseButton.button == sf::Mouse::Left) {
                m_parent->endLevel();
                return true;
            }
        }
    }
    return false;
}, nullptr) {
    sprite.setTexture(ResourceManager::get().getTexture("/cake.png"));
    sprite.setScale(0.1, 0.1);
    sprite.setPosition(pos);
    m_parent = parent;
}

void Cake::update(float delta) {
    if(m_parent) {
        if(auto player = m_parent->getPlayer()) {
            if(sprite.getGlobalBounds().contains(player->getPosition())) {
                finished = true;
            }
        }
    }
    if(finished)
        b.update(delta);
}

bool Cake::onEvent(sf::Event& e) {
    if(finished) {
        b.onEvent(e);
    }
    return false;
}

void Cake::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    if(finished)
        b.draw(window);
}