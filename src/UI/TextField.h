#include <utility>

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "../Application.h"
#include "../Tools/ResourceManager.h"

class TextField : public Button {
public:
    TextField(sf::Vector2f pos, const std::string &initalText, std::function<void(std::string)> onValueChanged) :
    Button(pos, initalText, nullptr, nullptr),
    m_cbOnValueChanged(std::move(onValueChanged)) {
        setText(initalText);
        currentText = initalText;
        m_text.setFont(ResourceManager::get().getFont("/ComicNeue-Regular.ttf"));
    }

    bool onEvent(sf::Event& event) override {
        if(event.type == sf::Event::MouseMoved) {
            highlight(containsPosition(Application::get().getWindow().getMousePosition()));
        }

        [this](sf::Event& event, Button& b){
            if(!m_hightlight)
                return false;

            if (event.type == sf::Event::TextEntered) {
                std::string string = currentText;
                if (event.text.unicode == '\b') {
                    if (!string.empty()) {
                        string.erase(string.size() - 1, 1);
                        updateString(string);
                    }
                } else if (event.text.unicode < 128) {
                    string += static_cast<char>(event.text.unicode);
                    updateString(string);
                }
                return true;
            }
            return false;
        }(event, *this);
        return Button::onEvent(event);
    }

    void updateString(std::string &string) {
        setText(string);
        currentText = string;
        m_cbOnValueChanged(string);
    }
protected:
    std::function<void(std::string)> m_cbOnValueChanged;
    std::string currentText;
};