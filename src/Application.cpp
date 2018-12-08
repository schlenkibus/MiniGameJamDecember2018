#include "Application.h"
#include "Menu/MenuScene.h"

Application::Application() : m_window(1366, 768) {
    m_window.setScene<MenuScene>();
}

GameWindow& Application::getWindow() {
    return m_window;
}

Application& Application::get() {
    static Application app;
    return app;
}

int Application::run() {
    return m_window.run();
}
