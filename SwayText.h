#ifndef SWAYTEXT_H
#define SWAYTEXT_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "SettingsMenu.h"

class SwayText1 {
public:
    SwayText1(sf::Text& text, sf::Vector2f originalPos)
        : text(text), originalPos(originalPos) {}

    void update(float time) {
        if (Animation) {
            float offset = std::sin(time * 2.f) * 5.f;
            text.setPosition(originalPos.x + offset, originalPos.y);
        }
    }

private:
    sf::Text& text;
    sf::Vector2f originalPos;
};
class SwayText2 {
public:
    SwayText2(sf::Text& text, sf::Vector2f originalPos)
        : text(text), originalPos(originalPos) {}

    void update(float time) {
        if (Animation) {
            float offset = std::sin(time * 2.f) * 5.f;
            text.setPosition(originalPos.x - offset, originalPos.y);
        }
    }

private:
    sf::Text& text;
    sf::Vector2f originalPos;
};

#endif // SWAYTEXT_H
