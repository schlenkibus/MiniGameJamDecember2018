#pragma once
#include "../LevelObject.h"

class Level3 : public LevelObject {
public:
    Level3(IngameScene& parent);
    int getLevelId() override {
        return 2;
    }
};