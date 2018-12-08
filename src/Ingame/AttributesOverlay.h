#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "../GameObject.h"
#include "../UI/Button.h"
#include "LevelObject.h"
#include "../UI/TextField.h"

class AttributesOverlay : public GameObject {
    public:
        AttributesOverlay(LevelObject::tAttributes attributes, std::function<void(LevelObject::tAttributes)> callback);
        void draw(sf::RenderWindow& window) override;
        void update(float deltaTime) override;
        bool onEvent(sf::Event& event) override;
    protected:
        sf::RectangleShape background;
        std::function<void(LevelObject::tAttributes)> cb;
        sf::Font& m_font;
        LevelObject::tAttributes m_attributes;

        void addAttributeLine(std::string key, std::string value);
        std::vector<std::tuple<sf::Text, TextField>> m_text;
        std::unique_ptr<Button> m_applyButton;

};