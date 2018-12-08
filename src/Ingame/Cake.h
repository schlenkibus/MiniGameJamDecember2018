#pragma once
#include "../GameObject.h"
#include <SFML/Graphics.hpp>
#include "../Tools/ResourceManager.h"
#include "../UI/Button.h"

class LevelObject;

class Cake : public GameObject {
public:
    Cake(LevelObject* parent, sf::Vector2f pos);
    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;

protected:
    bool finished = false;
    sf::Sprite sprite;
    LevelObject* m_parent;
    Button b;
};
