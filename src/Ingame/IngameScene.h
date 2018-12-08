#pragma once
#include "../GameScene.h"

class LevelObject;

class IngameScene : public GameScene {
public:
    explicit IngameScene(GameWindow& parent);
    LevelObject* getWorld() const;
};
