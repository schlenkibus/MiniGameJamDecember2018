#include "Tile.h"

static {
    Tile::vertecies{};
}

Tile::Tile(b2World *world, sf::Vector2f pos) : m_world(world), shape(vertecies) {
}

void Tile::update(float delta) {
    shape.
}

bool Tile::onEvent(sf::Event &e) {
    return GameObject::onEvent(e);
}

void Tile::draw(sf::RenderWindow &window) {
    shape.draw(window);
}

void Tile::onResize(sf::Event &resizeEvent) {
    GameObject::onResize(resizeEvent);
}
