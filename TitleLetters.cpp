#include "TitleLetters.h"
#include <cmath>

TitleLetters::TitleLetters(const std::string& text, const sf::Font& font, sf::Vector2f startPos, float charSize) {
    float x = startPos.x;
    float y = startPos.y;
    std::vector<float> angles = {-10, 5, -8, 7, -6, 8, -5, 10, -7, 6, -4, 5};

    for (size_t i = 0; i < text.size(); i++) {
        sf::Text outline;
        outline.setFont(font);
        outline.setString(text[i]);
        outline.setCharacterSize(static_cast<unsigned>(charSize+2));
        outline.setFillColor(sf::Color::Black);

        sf::Text letter;
        letter.setFont(font);
        letter.setString(text[i]);
        letter.setCharacterSize(static_cast<unsigned>(charSize));
        letter.setFillColor(sf::Color::White);

        sf::FloatRect bounds = letter.getLocalBounds();
        if (i > 0) x += bounds.width * 1.1f;

        letter.setOrigin(bounds.width / 2, bounds.height / 2);
        outline.setOrigin(bounds.width / 2, bounds.height / 2);

        letter.setPosition(x, y);
        outline.setPosition(x + 2, y + 2);  // Невелике зміщення для "обводки"

        letter.setRotation(angles[i % angles.size()]);
        outline.setRotation(angles[i % angles.size()]);

        initialPositions.push_back(letter.getPosition());
        letters.push_back(letter);
        outlines.push_back(outline);
    }
}

void TitleLetters::update(float swayOffset) {
    for (size_t i = 0; i < letters.size(); ++i) {
        sf::Vector2f pos = initialPositions[i];
        letters[i].setPosition(pos.x + swayOffset, pos.y);
        outlines[i].setPosition(pos.x + swayOffset + 2, pos.y + 2);  // Синхронізація
    }
}

void TitleLetters::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (size_t i = 0; i < letters.size(); ++i) {
        target.draw(outlines[i], states);  // Спочатку чорна обводка
        target.draw(letters[i], states);   // Потім основний білий текст
    }
}
