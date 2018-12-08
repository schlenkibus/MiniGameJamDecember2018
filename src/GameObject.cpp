#include "GameObject.h"
#include "Application.h"

const sf::Vector2f GameObject::getViewSize() const {
    return Application::get().getWindow().getRenderWindow().getView().getSize();
}

void GameObject::onResize(sf::Event &resizeEvent) {

}

bool GameObject::onEvent(sf::Event &event) {
    if(event.type == sf::Event::Resized)
        onResize(event);

    return false;
}
