#include "Overlay.h"
#include "../../Application.h"

void Overlay::update(float delta) {
    auto& window = Application::get().getWindow().getRenderWindow();
    auto oldView = window.getView();
    window.setView(window.getDefaultView());
    m_controls.update(delta);
    window.setView(oldView);
}

bool Overlay::onEvent(sf::Event &e) {
    auto& window = Application::get().getWindow().getRenderWindow();
    auto oldView = window.getView();
    window.setView(window.getDefaultView());
    auto ret = m_controls.onEvent(e);
    window.setView(oldView);
    return ret;
}

void Overlay::draw(sf::RenderWindow &window) {
    auto oldView = window.getView();
    window.setView(window.getDefaultView());
    m_controls.draw(window);
    window.setView(oldView);
}

void Overlay::addChild(GameObject *go) {
    m_controls.appendChild(go);
}

void Overlay::onResize(sf::Event &resizeEvent) {
    GameObject::onResize(resizeEvent);
}
