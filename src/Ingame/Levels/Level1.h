#pragma once
#include "../LevelObject.h"

class Level1 : public LevelObject {
public:
    Level1(IngameScene& parent);
    int getLevelId() override {
        return 0;
    }
};