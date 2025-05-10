#ifndef TITLELETTERS_H
#define TITLELETTERS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "SettingsMenu.h"

class TitleLetters : public sf::Drawable { // Наследуемся от sf::Drawable
public:
    TitleLetters(const std::string& text, const sf::Font& font, sf::Vector2f startPos, float charSize);

    void update(float swayOffset);

    // draw переопределяется из sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<sf::Text> letters;
    std::vector<sf::Vector2f> initialPositions;
    std::vector<sf::Text> outlines;
};

#endif // TITLELETTERS_H
