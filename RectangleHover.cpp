//
// Created by artem on 03.04.2025.
//

#include "RectangleHover.h"

std::unordered_map<sf::RectangleShape*, sf::Vector2f> RectangleHover::originalSizes;
std::unordered_map<sf::RectangleShape*, sf::Vector2f> RectangleHover::originalPositions;

void RectangleHover::applyHoverEffect(sf::RectangleShape& rectangle, sf::RenderWindow& window, bool animationEnabled) {
    if (!animationEnabled) return;

    if (originalSizes.find(&rectangle) == originalSizes.end()) {
        originalSizes[&rectangle] = rectangle.getSize();
        originalPositions[&rectangle] = rectangle.getPosition();
    }

    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (rectangle.getGlobalBounds().contains(worldPos)) {
        if (rectangle.getSize() == originalSizes[&rectangle]) {
            sf::Vector2f newSize = originalSizes[&rectangle] * 1.1f;
            sf::Vector2f newPosition = {
                originalPositions[&rectangle].x - (newSize.x - originalSizes[&rectangle].x) / 2,
                originalPositions[&rectangle].y - (newSize.y - originalSizes[&rectangle].y) / 2
            };
            rectangle.setSize(newSize);
            rectangle.setPosition(newPosition);
        }
    } else {
        if (rectangle.getSize() != originalSizes[&rectangle]) {
            rectangle.setSize(originalSizes[&rectangle]);
            rectangle.setPosition(originalPositions[&rectangle]);
        }
    }
}
