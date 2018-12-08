#pragma once
#include "../LevelObject.h"

class Level2 : public LevelObject {
public:
    Level2(IngameScene& parent);
    int getLevelId() override {
        return 1;
    }
};