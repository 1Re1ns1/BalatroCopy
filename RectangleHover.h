//
// Created by artem on 03.04.2025.
//

#ifndef RECTANGLEHOVER_H
#define RECTANGLEHOVER_H


#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class RectangleHover {
public:
    static void applyHoverEffect(sf::RectangleShape& rectangle, sf::RenderWindow& window, bool animationEnabled);

private:
    static std::unordered_map<sf::RectangleShape*, sf::Vector2f> originalSizes;
    static std::unordered_map<sf::RectangleShape*, sf::Vector2f> originalPositions;
};




#endif //RECTANGLEHOVER_H
