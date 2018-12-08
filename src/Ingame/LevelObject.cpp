#include <iostream>
#include "LevelObject.h"
#include "IngameScene.h"
#include "../Application.h"
#include "Details/TestObject.h"

LevelObject::LevelObject(IngameScene &parent) :
    m_parent(parent),
    m_terrain(&m_world, []() {
        std::vector<b2Vec2> ret;
        ret.reserve(100);
        ret.emplace_back(b2Vec2(0, 50));
        for(int x = 1; x < 99; x++) {
            auto y = x > 20 && x < 80 ? -30 : 0;
            ret.emplace_back(b2Vec2(x * 5, y));
        }
        ret.emplace_back(b2Vec2(99 * 5, 50));
        return ret;
    }()),
    m_world(b2Vec2(0, 98.1f)) {
    Application::get().getWindow().getRenderWindow().setView(m_view);
    m_poi = m_view.getCenter();
    m_poi.y = m_poi.y - 200;
}

void LevelObject::update(float delta) {
    updateCamera();
    //moveCamera();

    static sf::Clock clock;
    if(clock.getElapsedTime().asSeconds() >= 1./60) {
        m_world.Step(1.f/60, 3, 5);
        clock.restart();
    }

    for(auto& go: m_objects) {
        go->update(delta);
    }

    m_terrain.update(delta);
}

bool LevelObject::onEvent(sf::Event &e) {
    moveCamera();

    if(e.type == sf::Event::KeyReleased) {
        handleZoom(e);
    }

    if(e.type == sf::Event::MouseButtonReleased) {
        if(e.mouseButton.button == sf::Mouse::Button::Left) {
            auto mousePos = Application::get().getWindow().getMousePosition();
            m_objects.push_back(std::make_unique<TestObject>(&m_world, sf::Vector2f(mousePos.x, mousePos.y)));
        }
    }

    for(auto& go: m_objects) {
        if(go->onEvent(e))
            return true;
    }

    return m_terrain.onEvent(e);
}

void LevelObject::draw(sf::RenderWindow &window) {
    m_terrain.draw(window);
    for(auto& go: m_objects) {
        go->draw(window);
    }
}

void LevelObject::moveCamera() {
    static sf::Clock throttler;
    if(throttler.getElapsedTime().asSeconds() < 0.01)
        return;
    throttler.restart();


    sf::View view = Application::get().getWindow().getRenderWindow().getView();
    auto& window = Application::get().getWindow().getRenderWindow();
    auto mousePos = Application::get().getWindow().getMousePositionRelativeToWindow();

    const bool rightBorder = mousePos.x > window.getSize().x - 50;
    const bool leftBorder = mousePos.x < 50;
    const bool topBorder = mousePos.y < 50;
    const bool bottomBorder = mousePos.y > window.getSize().y - 50;

    auto moveFactor = 4 * m_zoom;


    if(rightBorder)
        m_poi.x += moveFactor;
    if(leftBorder)
        m_poi.x -= moveFactor;
    if(topBorder)
        m_poi.y -= moveFactor;
    if(bottomBorder)
        m_poi.y += moveFactor;
}

bool LevelObject::handleZoom(sf::Event &event) {
    sf::View view = Application::get().getWindow().getRenderWindow().getView();

    if(event.key.code == sf::Keyboard::PageDown) {
        m_zoom *= 2;
        view.zoom(2);
    } else if(event.key.code == sf::Keyboard::PageUp) {
        m_zoom *= 0.5;
        view.zoom(0.5f);
    } else {
        return false;
    }

    auto& window = Application::get().getWindow().getRenderWindow();
    window.setView(view);
    return true;
}

void LevelObject::onResize(sf::Event &resizeEvent) {
    GameObject::onResize(resizeEvent);
}

void LevelObject::updateCamera() {
    static sf::Clock throttle;
    if(throttle.getElapsedTime().asSeconds() > 0.01) {
        auto y = m_view.getCenter().y;
        auto x = m_view.getCenter().x;
        float newX = static_cast<float>(x + (m_poi.x - x) * 0.1);
        float newY = static_cast<float>(y + (m_poi.y - y) * 0.1);
        m_view.setCenter(newX, newY);
        Application::get().getWindow().getRenderWindow().setView(m_view);
        throttle.restart();
    }
}
