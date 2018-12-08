#include <iostream>
#include "MenuScene.h"
#include "../GameWindow.h"
#include "../UI/Label.h"
#include "../UI/GenericReactiveLabel.h"
#include "../UI/Button.h"
#include "../Ingame/IngameScene.h"
#include "../UI/Overlay/Overlay.h"

MenuScene::MenuScene(GameWindow& parent) : GameScene(parent) {
    m_gameObjects.push_back(std::make_unique<Overlay>());

    auto overlay = dynamic_cast<Overlay*>(m_gameObjects.back().get());
    if(overlay) {
        overlay->addChild(new Label(sf::Vector2f(300, 200), "Mini Game Jam December 2018!"));
        overlay->addChild(new GenericReactiveLabel([](float delta, Label& l) {
            l.setText(std::string("frameTime:") + std::to_string(delta) + "s");
        }, sf::Vector2f(0, 0)));
        overlay->addChild(new Button(sf::Vector2f(300, 450), "Quit!", [&](sf::Event& e, Button& b){
            static int counter = 0;
            if(e.type == sf::Event::MouseButtonReleased &&
               e.mouseButton.button == sf::Mouse::Left) {
                if(b.containsPosition(m_parent.getMousePosition()))
                {
                    m_parent.getRenderWindow().close();
                    return true;
                }
            }
            return false;
        }, nullptr));

        overlay->addChild(new Button(sf::Vector2f(300, 350), "Play", [&](sf::Event& e, Button& b){
            if(e.type == sf::Event::MouseButtonReleased &&
               e.mouseButton.button == sf::Mouse::Left) {
                if(b.containsPosition(m_parent.getMousePosition()))
                {
                    m_parent.setScene<IngameScene>();
                    return true;
                }
            }
            return false;
        }, nullptr));
    }
}