#include <SFML/Graphics/RenderWindow.hpp>
#include "PolyShape.h"
#include "../Tools/ResourceManager.h"

PolyShape::PolyShape(const std::vector<sf::Vector2f> &polygons) {
    calcObject(polygons);
    m_shape.setTexture(&ResourceManager::get().getTexture("/ground.png"));
    ResourceManager::get().getTexture("/ground.png").setRepeated(true);
    m_shape.setTextureRect(sf::IntRect(0, 0, static_cast<int>(m_shape.getLocalBounds().width),
                                       static_cast<int>(m_shape.getLocalBounds().height)));
}

void PolyShape::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
}

void PolyShape::setPosition(sf::Vector2<float> vector2) {
    m_shape.setPosition(vector2);
}

void PolyShape::setRotation(int rot) {
    m_shape.setRotation(rot);
}

void PolyShape::calcObject(const std::vector<sf::Vector2f> &polygons) {
    m_shape.setPointCount(polygons.size() + 2);
    std::size_t index = 1;
    m_shape.setPoint(0, sf::Vector2f(0, 5000));
    for(auto& point: polygons) {
        m_shape.setPoint(index, point);
        index++;
    }
    m_shape.setPoint(polygons.size() + 1, sf::Vector2f(m_shape.getPoint(index-1).x + 1, 5000));
}

