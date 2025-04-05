//
// Created by artem on 18.03.2025.
//

#ifndef MENUBALATRO_H
#define MENUBALATRO_H
#include <SFML/Graphics.hpp>

// Объявление функции меню
void MenuBalatro(sf::RenderWindow& window);
void ApplyHoverEffect(sf::RectangleShape& rectangle, sf::RenderWindow& window);
void ApplyHoverEffectText(sf::Text& text,sf::Text& textOutline, sf::RenderWindow& window);
void FadeOut(sf::RenderWindow& window, sf::Sprite& backgroundSprite, std::vector<sf::Text>& letters,
             sf::Text& outlinetitle2, sf::Text& outlinetitle3,
             sf::Text& outlinesetings, sf::Text& setingstitle,
             sf::Text& title3, sf::Text& title2,
             sf::Text& version, sf::Text& NameUser,
             bool& finished);
#endif //MENUBALATRO_H

