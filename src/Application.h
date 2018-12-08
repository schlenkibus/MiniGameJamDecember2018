#pragma once

#include "GameWindow.h"

class Application {
    Application();
public:
    static Application& get();
    int run();
    GameWindow& getWindow();
private:
    GameWindow m_window;
};
