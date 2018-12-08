#include <functional>
#include "Button.h"
#include "../Tools/ResourceManager.h"
#include "../Application.h"

Button::Button(sf::Vector2f pos, std::string text,
        std::function<bool(sf::Event& e, Button&)>&& eventCallBack,
        std::function<void(float, Button&)>&& updateCallBack)
        : m_text("", ResourceManager::get().getFont("/Wendy_One/WendyOne-Regular.ttf")),
        m_shape(sf::Vector2f(100, 30)),
        m_eventCallBack(std::move(eventCallBack)),
        m_updateCallBack(std::move(updateCallBack)) {
    m_text.setString(text);
    m_text.setPosition(pos);
    m_shape.setPosition(m_text.getPosition());
    m_shape.move(0, m_text.getLocalBounds().height / 3.f);
    fitToText();

    m_shape.setFillColor(sf::Color::Transparent);
    m_shape.setOutlineColor(sf::Color::Red);
    //highlight(containsPosition(Application::get().getWindow().getMousePosition()));
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
    window.draw(m_text);
}

void Button::update(float d) {
    if(m_updateCallBack)
        m_updateCallBack(d, *this);

    fitToText();
}

bool Button::onEvent(sf::Event &e) {
    if(e.type == sf::Event::MouseMoved)
        highlight(containsPosition(Application::get().getWindow().getMousePosition()));

    if(m_eventCallBack)
        return m_eventCallBack(e, *this);

    return GameObject::onEvent(e);
}

void Button::fitToText() {
    const auto size = sf::Vector2f(m_text.getLocalBounds().width + getPadding(),
                                   m_text.getLocalBounds().height + getPadding());
    if(size != m_shape.getSize())
        m_shape.setSize(size);
}

void Button::highlight(bool highlight) {
    m_shape.setOutlineThickness(static_cast<float>(highlight ? 4 : 2));
    m_hightlight = highlight;
}

const bool Button::containsPosition(const sf::Vector2i& pos) const {
    const auto floatPos = sf::Vector2f(pos);
    return m_shape.getGlobalBounds().contains(floatPos) || m_text.getGlobalBounds().contains(floatPos);
}

void Button::setText(std::string text) {
    m_text.setString(text);
    fitToText();
}

void Button::onResize(sf::Event& resizeEvent) {
    auto oldPos = m_text.getPosition();
    auto oldView = Application::get().getWindow().getOldViewPort();
    m_text.setPosition(oldPos);
    fitToText();
}

const float Button::getPadding() const {
    return 5;
}
