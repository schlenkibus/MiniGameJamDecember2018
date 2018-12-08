#include "GameScene.h"


GameScene::GameScene(GameWindow &parent) : m_parent(parent) {
}


void GameScene::draw(sf::RenderWindow &window) {
    for(auto& go: m_gameObjects) {
        go->draw(window);
    }
}

void GameScene::update(float deltaTime) {
    for(auto& go: m_gameObjects) {
        go->update(deltaTime);
    }
}

void GameScene::onEvent(sf::Event& event) {
    for(auto& go: m_gameObjects) {
        if(go->onEvent(event))
            break;
    }
}
