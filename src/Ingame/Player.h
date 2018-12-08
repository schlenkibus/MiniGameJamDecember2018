#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../GameObject.h"

class b2World;
class b2Body;

class Player : public GameObject {
public:
    Player(sf::Vector2f pos, b2World* world);

    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;
    const sf::Vector2f getPosition() const;
protected:
    sf::RectangleShape m_sprite;
    b2Body* m_body;
    b2World* m_world;
    b2PolygonShape m_shape;

    struct Movement {
        bool left = false;
        bool right = false;
        bool up = false;

        void update(float delta) {
            if((left && right) || (!left && !right)) {
                if(xSpeed > 0)
                    xSpeed -= accellerationX;
                else
                    xSpeed += accellerationX;
            }

            if(up) {
                ySpeed = 300;
            } else {
                ySpeed = 0;
            }

            if(left) {
                if(xSpeed > -maxSpeedX)
                    xSpeed -= accellerationX;
            } else if(right) {
                if(xSpeed < maxSpeedX)
                    xSpeed += accellerationX;
            }

            //Sanitze:
            xSpeed = std::max(std::min(xSpeed, maxSpeedX), -maxSpeedX);
        }

        float accellerationX = 0.2;
        float maxSpeedX = 60;

        float xSpeed = 0;
        float ySpeed = 0;
    };

    Movement movement;
};