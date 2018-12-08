#pragma once
#include <SFML/Graphics.hpp>
#include "GameScene.h"

class GameWindow {
public:
    GameWindow(unsigned int w, unsigned int h);

    template<class T>
    void setScene() {
        m_scene.reset(new T(*this));
    }

    int run();

    const sf::Vector2i getMousePosition() const;
    const sf::Vector2i getMousePositionRelativeToWindow() const;
    sf::RenderWindow& getRenderWindow() const;
    const sf::View& getOldViewPort() const;
    GameScene* getScene() const;

private:
    sf::RenderWindow m_window;
    std::unique_ptr<GameScene> m_scene;
    sf::View m_oldView;

    void updateView(const sf::Event &event);
};
