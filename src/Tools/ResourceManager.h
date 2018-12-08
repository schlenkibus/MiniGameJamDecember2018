#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class ResourceManager {
public:
    ResourceManager();
    sf::Texture& getTexture(std::string file);
    sf::Font& getFont(std::string name);
    static ResourceManager& get();
private:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Font> m_fonts;
};
