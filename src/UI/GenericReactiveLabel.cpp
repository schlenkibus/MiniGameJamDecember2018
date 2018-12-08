//
// Created by justus on 24.08.18.
//

#include "GenericReactiveLabel.h"
#include "../Tools/ResourceManager.h"

GenericReactiveLabel::GenericReactiveLabel(std::function<void(float, Label&)> cb, sf::Vector2f pos) :
Label(pos, ""), m_cb(cb) {

}

void GenericReactiveLabel::update(float deltaTime) {
    m_cb(deltaTime, *this);
}

void GenericReactiveLabel::onResize(sf::Event &resizeEvent) {
    Label::onResize(resizeEvent);
}
