//
// Created by artem on 03.04.2025.
//

#ifndef TEXTANIMATOR_H
#define TEXTANIMATOR_H
#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

#pragma once
#include <SFML/Graphics.hpp>

class TextAnimator {
public:
    static sf::Text createText(const std::string& str, const sf::Font& font, unsigned int size, sf::Color color);
    static void applyHoverEffect(sf::Text& text, sf::Text& outline, sf::RenderWindow& window);
    static void drawWithOutline(sf::RenderWindow& window, const sf::Text& text, const sf::Text& outline);
};






#endif //TEXTANIMATOR_H
