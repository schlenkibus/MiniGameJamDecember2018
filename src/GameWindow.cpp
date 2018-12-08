#include "GameWindow.h"

GameWindow::GameWindow(unsigned int w, unsigned int h) : m_window(sf::VideoMode(w, h), "BMGJ", sf::Style::Fullscreen) {

}

int GameWindow::run() {

    static sf::Clock mainClock{};

    sf::Event e{};
    mainClock.restart();

    while(m_window.isOpen()) {

        while(m_window.pollEvent(e)) {
            if(e.type == sf::Event::Closed)
                m_window.close();
            if(e.type == sf::Event::Resized)
                updateView(e);
            m_scene->onEvent(e);
        }

        m_scene->update(mainClock.getElapsedTime().asSeconds());
        mainClock.restart();

        m_window.clear();
        m_scene->draw(m_window);
        m_window.display();
    }

    return 0;
}

const sf::Vector2i GameWindow::getMousePosition() const {
    auto pixPos =  sf::Mouse::getPosition(m_window);
    auto coordPos = m_window.mapPixelToCoords(pixPos);
    return sf::Vector2i(static_cast<int>(coordPos.x), static_cast<int>(coordPos.y));
}

const sf::Vector2i GameWindow::getMousePositionRelativeToWindow() const {
    return sf::Mouse::getPosition(m_window);
}

sf::RenderWindow &GameWindow::getRenderWindow() const {
    return const_cast<sf::RenderWindow&>(m_window);
}

void GameWindow::updateView(const sf::Event &event) {
    m_oldView = m_window.getView();
    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
    m_window.setView(sf::View(visibleArea));
}

const sf::View &GameWindow::getOldViewPort() const {
    return m_oldView;
}

GameScene *GameWindow::getScene() const {
    return m_scene.get();
}
