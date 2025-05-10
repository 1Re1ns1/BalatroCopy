#include "TextAnimator.h"
#include <unordered_map>
#include <cmath>

#include "SettingsMenu.h"

namespace {
    std::unordered_map<const sf::Text*, float> scaleFactors;
    const float scaleSpeed = 0.1f;
    const float maxScale = 1.2f;
    const float minScale = 1.0f;
    const float outlineScaleFactor = 1.1f;
}

sf::Text TextAnimator::createText(const std::string& str, const sf::Font& font, unsigned int size, sf::Color color) {
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    return text;
}

void TextAnimator::applyHoverEffect(sf::Text& text, sf::Text& outline, sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (Animation) {
        if (scaleFactors.find(&text) == scaleFactors.end()) {
            scaleFactors[&text] = minScale;
        }

        float& scale = scaleFactors[&text];
        bool isHovered = text.getGlobalBounds().contains(mousePos);

        if (isHovered) {
            scale = std::min(scale + (maxScale - scale) * scaleSpeed, maxScale);
        } else {
            scale = std::max(scale - (scale - minScale) * scaleSpeed, minScale);
        }

        text.setScale(scale, scale);
        outline.setScale(scale * outlineScaleFactor, scale * outlineScaleFactor);

        if (!isHovered) {
            outline.setScale(0.f, 0.f);
        }
    }
}

void TextAnimator::drawWithOutline(sf::RenderWindow& window, const sf::Text& text, const sf::Text& outline) {
    window.draw(outline);
    window.draw(text);
}
