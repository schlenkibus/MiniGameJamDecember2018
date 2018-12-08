#include "Level1.h"
#include "../ModulateableObject.h"
#include "../Cake.h"
#include "../Player.h"

Level1::Level1(IngameScene &parent)  : LevelObject(parent) {
    m_objects.emplace_back(std::make_unique<Player>(sf::Vector2f(300, -100), &m_world));
    m_player = dynamic_cast<Player*>(m_objects.back().get());
    m_objects.emplace_back(std::make_unique<Cake>(this, sf::Vector2f(600, -50)));
}