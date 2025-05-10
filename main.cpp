#include <SFML/Graphics.hpp>

#include "AudioManager.h"
#include "MenuBalatro.h"
#include "HadeMenu.h"
int main() {
    sf::RenderWindow window(sf::VideoMode(), "Balatro", sf::Style::Fullscreen);
    // Запуск меню
    HadeMenu(window);
    AudioManager::loadConfig();
    MenuBalatro(window);

    return 0;
}
