#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../GameObject.h"

class Label : public GameObject {
public:
    Label(sf::Vector2f pos, std::string name);
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    bool onEvent(sf::Event& event) override;
    void setText(std::string s);
protected:
    void onResize(sf::Event& resizeEvent) override;
    sf::Text m_text;
};