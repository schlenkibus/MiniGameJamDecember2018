#pragma once

#include <SFML/Window/Event.hpp>
#include "../GameObject.h"
#include "Details/TerrainObject.h"

class IngameScene;

class LevelObject : public GameObject {
public:
    explicit LevelObject(IngameScene& parent);

    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;
protected:
    b2World m_world;
    void onResize(sf::Event& resizeEvent) override;
    IngameScene& m_parent;
    TerrainObject m_terrain;
    //Water m_water;
    sf::View m_view;
    sf::Vector2f m_poi;
    std::vector<std::unique_ptr<GameObject>> m_objects;

    void moveCamera();
    void updateCamera();
    bool handleZoom(sf::Event &event);

    float m_zoom = 1;
};