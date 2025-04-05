//
// Created by artem on 03.04.2025.
//

#ifndef MENUPAUSE_H
#define MENUPAUSE_H



#pragma once
#include <SFML/Graphics.hpp>

class PauseMenu {
public:
    PauseMenu(const sf::Font& font, const sf::Vector2u& windowSize);
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window, bool& resumeGame, bool& openSettings, bool& saveGame, bool& exitGame);
    bool isOpen() const;
    void open();
    void close();
    void exitgame();

private:
    sf::RectangleShape background;
    sf::Text resumeText;
    sf::Text saveText;
    sf::Text settingsText;
    sf::Text exitText;
    bool visible;
};




#endif //MENUPAUSE_H
