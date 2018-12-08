#include <cassert>
#include <iostream>
#include "ResourceManager.h"

ResourceManager::ResourceManager() {

}

sf::Font& ResourceManager::getFont(std::string name) {
    auto f = m_fonts.find(name);

    if(f != m_fonts.end())
        return f->second;

    if(!m_fonts[name].loadFromFile("../resources/fonts" + name))
        assert(false);

    return m_fonts[name];
}

sf::Texture& ResourceManager::getTexture(std::string file) {
    auto a = m_textures.find(file);

    if (a != m_textures.end())
        return a->second;

    if (!m_textures[file].loadFromFile("../resources/textures" + file))
        assert(false);

    return m_textures[file];
}

ResourceManager &ResourceManager::get() {
    static ResourceManager rm;
    return rm;
}
