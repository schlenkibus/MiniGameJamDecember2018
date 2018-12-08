#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"


class GameWindow;

class GameScene {
public:
    explicit GameScene(GameWindow& parent);
    virtual void draw(sf::RenderWindow& window);
    virtual void update(float deltaTime);
    virtual void onEvent(sf::Event& event);
protected:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    GameWindow& m_parent;
};
