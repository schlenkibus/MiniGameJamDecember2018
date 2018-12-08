#pragma once

#include <SFML/Window/Event.hpp>
#include <unordered_map>
#include "../GameObject.h"
#include "Details/TerrainObject.h"
#include <functional>
#include <iostream>

class IngameScene;
class Player;
class AttributesOverlay;

class LevelObject : public GameObject {
public:
    typedef std::unordered_map<std::string, std::string> tAttributes;
    explicit LevelObject(IngameScene& parent);

    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;
    void openAttributesEditor(tAttributes, std::function<void(tAttributes)> callback);
    void removeOverlays();
    Player* getPlayer() const {
        return m_player;
    }
    void endLevel() {
        std::cout << "Level done!\n";
    }
protected:
    b2World m_world;
    void onResize(sf::Event& resizeEvent) override;
    IngameScene& m_parent;
    TerrainObject m_terrain;
    Player* m_player;
    //Water m_water;
    sf::View m_view;
    sf::Vector2f m_poi;
    std::vector<std::unique_ptr<GameObject>> m_objects;

    void moveCamera();
    void updateCamera();
    bool handleZoom(sf::Event &event);

    float m_zoom = 1;
};