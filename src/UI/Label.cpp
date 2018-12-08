#include "Label.h"
#include "../Tools/ResourceManager.h"

Label::Label(sf::Vector2f pos, std::string name) :
    m_text(name, ResourceManager::get().getFont("/Wendy_One/WendyOne-Regular.ttf")) {
    m_text.setPosition(pos);
}

bool Label::onEvent(sf::Event &event) {
    return false;
}

void Label::update(float deltaTime) {
}

void Label::draw(sf::RenderWindow &window) {
    window.draw(m_text);
}

void Label::setText(std::string s) {
    m_text.setString(s);
}

void Label::onResize(sf::Event &resizeEvent) {
    GameObject::onResize(resizeEvent);
}

