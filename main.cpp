#include <SFML/Graphics.hpp>

#include "AudioManager.h"
#include "MenuBalatro.h"
#include "HadeMenu.h"
#include <SFML/Graphics.hpp>

sf::RenderWindow window;
bool isFullscreen = false;

int main() {
    AudioManager::init();
    sf::RenderWindow window(sf::VideoMode(), "Balatro", sf::Style::Fullscreen);
    // Запуск меню
    HadeMenu(window);
    AudioManager::loadConfig();
    MenuBalatro(window);

    return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.