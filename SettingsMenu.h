//
// Created by artem on 26.03.2025.
//

#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H
#include <SFML/Graphics.hpp>

inline bool Animation = true;
void SettingsMenu(sf::RenderWindow& window);
extern sf::RenderWindow window;
extern bool isFullscreen;

void createWindow(bool fullscreen);



#endif //SETTINGSMENU_H
