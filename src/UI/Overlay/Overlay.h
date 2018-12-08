#pragma once
#include "../../GameObject.h"
#include "ControlOwner.h"

class Overlay : public GameObject {
public:
    Overlay() = default;
    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;
    void addChild(GameObject* go);
protected:
    void onResize(sf::Event& resizeEvent) override;
    ControlOwner m_controls;
};
