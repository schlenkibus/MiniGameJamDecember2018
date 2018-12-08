#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../GameObject.h"
#include <functional>

class Button : public GameObject {
public:
    explicit Button(sf::Vector2f pos, std::string text,
            std::function<bool(sf::Event&, Button&)>&& eventCallBack,
            std::function<void(float, Button&)>&& updateCallBack);

    void draw(sf::RenderWindow& window) override;
    void update(float d) override;
    bool onEvent(sf::Event& e) override;
    void highlight(bool highlight);
    const bool isHighlighted() const {
        return m_hightlight;
    }
    const bool containsPosition(const sf::Vector2i& pos) const;
    void setText(std::string text);
protected:
    void onResize(sf::Event& resizeEvent) override;
    const float getPadding() const;
    sf::Text m_text;
    sf::RectangleShape m_shape;
    std::function<bool(sf::Event&, Button&)> m_eventCallBack;
    std::function<void(float, Button&)> m_updateCallBack;

    bool m_hightlight = false;
    void fitToText();
};