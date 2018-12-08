#include <iostream>
#include "LevelObject.h"
#include "IngameScene.h"
#include "../Application.h"
#include "Details/TestObject.h"
#include "Player.h"
#include "ModulateableObject.h"
#include "AttributesOverlay.h"
#include "Cake.h"

int gety(int x) {
    if(x > 20 && x < 80) {
        return -50;
    }
    return 0;
}

LevelObject::LevelObject(IngameScene &parent) :
    m_parent(parent),
    m_terrain(&m_world, []() {
        std::vector<b2Vec2> ret;
        ret.reserve(500);
        ret.emplace_back(b2Vec2(0, 5000));
        for(int x = 1; x < 499; x++) {
            auto y = gety(x);
            ret.emplace_back(b2Vec2(x * 5, y));
        }
        ret.emplace_back(b2Vec2(499 * 5, 5000));
        return ret;
    }()),
    m_world(b2Vec2(0, 9.81f)) {
    Application::get().getWindow().getRenderWindow().setView(m_view);
    m_poi = m_view.getCenter();
    m_poi.y = m_poi.y - 200;

    m_objects.emplace_back(std::make_unique<Player>(sf::Vector2f(300, -100), &m_world));
    m_player = dynamic_cast<Player*>(m_objects.back().get());
    m_objects.emplace_back(std::make_unique<ModulateableObject>(this, &m_world, sf::Vector2f( 100, -80), sf::Vector2f(30, 50)));
    m_objects.emplace_back(std::make_unique<Cake>(this, sf::Vector2f(600, -80)));
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

void LevelObject::removeOverlays() {
    typedef decltype(m_objects.begin()) tIt;
    std::vector<tIt> foundElements;
    for(auto it = m_objects.begin(); it != m_objects.end(); it++) {
        if(dynamic_cast<AttributesOverlay*>(it->get()))
            foundElements.emplace_back(it);
    }

    for(auto target: foundElements) {
        m_objects.erase(target);
    }
}

bool LevelObject::onEvent(sf::Event &e) {
    moveCamera();

    if(e.type == sf::Event::KeyReleased) {
        handleZoom(e);
        if(e.key.code == sf::Keyboard::Escape) {
            removeOverlays();
        }
    }



    /*if(e.type == sf::Event::MouseButtonReleased) {
        if(e.mouseButton.button == sf::Mouse::Button::Left) {
            auto mousePos = Application::get().getWindow().getMousePosition();
            m_objects.push_back(std::make_unique<TestObject>(&m_world, sf::Vector2f(mousePos.x, mousePos.y)));
        }
    }*/

    for(auto& go: m_objects) {
        if(go != nullptr)
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
    m_poi = m_player->getPosition();
}

bool LevelObject::handleZoom(sf::Event &event) {

    if(event.key.code == sf::Keyboard::PageDown) {
        m_zoom *= 2;
        m_view.zoom(2);
    } else if(event.key.code == sf::Keyboard::PageUp) {
        m_zoom *= 0.5;
        m_view.zoom(0.5f);
    } else {
        return false;
    }

    auto& window = Application::get().getWindow().getRenderWindow();
    window.setView(m_view);
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
        auto newX = static_cast<float>(x + (m_poi.x - x) * 0.01);
        auto newY = static_cast<float>(y + (m_poi.y - y) * 0.01);
        m_view.setCenter(newX, newY);
        Application::get().getWindow().getRenderWindow().setView(m_view);
        throttle.restart();
    }
}

void LevelObject::openAttributesEditor(LevelObject::tAttributes attributes, std::function<void(tAttributes)> callback) {
    removeOverlays();
    m_objects.emplace_back(std::make_unique<AttributesOverlay>(attributes, callback));
}
