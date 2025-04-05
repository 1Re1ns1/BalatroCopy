#ifndef SWAYTEXT_H
#define SWAYTEXT_H

#include <SFML/Graphics.hpp>
#include <cmath>

class SwayText1 {
public:
    SwayText1(sf::Text& text, sf::Vector2f originalPos)
        : text(text), originalPos(originalPos) {}

    void update(float time) {
        float offset = std::sin(time * 2.f) * 5.f;
        text.setPosition(originalPos.x + offset, originalPos.y);
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
        float offset = std::sin(time * 2.f) * 5.f;
        text.setPosition(originalPos.x - offset, originalPos.y);
    }

private:
    sf::Text& text;
    sf::Vector2f originalPos;
};

#endif // SWAYTEXT_H
