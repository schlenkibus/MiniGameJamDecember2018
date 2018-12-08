#pragma once

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class PolyShape {
public:
    explicit PolyShape(const std::vector<sf::Vector2f>& polygons);
    void draw(sf::RenderWindow& window);
protected:
    void calcObject(const std::vector<sf::Vector2f> &polygons);
    sf::ConvexShape m_shape;

    void setPosition(sf::Vector2<float> vector2);
    void setRotation(int rot);
    friend class TerrainObject;
};
