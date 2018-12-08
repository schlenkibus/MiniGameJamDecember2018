#include <utility>

#include <utility>
#include <iostream>

#include "AttributesOverlay.h"
#include "../Application.h"
#include "../Tools/ResourceManager.h"

AttributesOverlay::AttributesOverlay(LevelObject::tAttributes attributes, std::function<void(LevelObject::tAttributes)> callback) : m_font{ResourceManager::get().getFont("/ComicNeue-Regular.ttf")} {

    m_attributes = attributes;
    cb = std::move(callback);
    for(const auto&[key, value]: attributes) {
        addAttributeLine(key, value);
    }

    //add Apply Button
    /*
     * sf::Vector2f pos, std::string text,
            std::function<bool(sf::Event&, Button&)>&& eventCallBack,
            std::function<void(float, Button&)>&& updateCallBack
     */
    auto x = std::stoi(m_attributes["x"]);
    auto y = std::stoi(m_attributes["y"]);
    m_applyButton = std::make_unique<Button>(sf::Vector2f(x - 50, y - 50), "Apply!", [&, this](sf::Event& e, Button& b) {
        if(e.type == sf::Event::MouseButtonReleased &&
            e.mouseButton.button == sf::Mouse::Left &&b.containsPosition(Application::get().getWindow().getMousePosition())) {
            std::cout << "applying!" << std::endl;
            cb(m_attributes);
            return true;
        }
        return false;
    }, [] (float delta, Button& b) {
    });

    background.setPosition(x - 50, y - 50);
    background.setSize({300, 400});
    background.setFillColor(sf::Color(46, 255, 0, 127));
}

void AttributesOverlay::addAttributeLine(std::string key, std::string value) {
    auto lastYPos = std::stoi(m_attributes["y"]);
    auto x = std::stoi(m_attributes["x"]);
    if(!m_text.empty())
        lastYPos = static_cast<int>(std::get<0>(m_text.back()).getPosition().y);

    const auto keyCopy = key;
    m_text.emplace_back(std::make_tuple<sf::Text, TextField>({key, m_font, 30},
            {sf::Vector2f(x+100, lastYPos + 40), value, [=](std::string newValue) {
                m_attributes[keyCopy] = newValue;
            }}
            ));
    std::get<0>(m_text.back()).setPosition(x, lastYPos + 40);
}

void AttributesOverlay::draw(sf::RenderWindow &window) {
    window.draw(background);
    for(auto& t: m_text) {
        window.draw(std::get<0>(t));
        std::get<1>(t).draw(window);
    }
    m_applyButton->draw(window);
}

void AttributesOverlay::update(float deltaTime) {
    m_applyButton->update(deltaTime);
    for(auto& entry: m_text) {
        auto& valueInput = std::get<1>(entry);
        valueInput.update(deltaTime);
    }
}

bool AttributesOverlay::onEvent(sf::Event &event) {
    for(auto& entry: m_text) {
        auto& valueInput = std::get<1>(entry);
        valueInput.onEvent(event);
    }
    m_applyButton->onEvent(event);
    return GameObject::onEvent(event);
}


