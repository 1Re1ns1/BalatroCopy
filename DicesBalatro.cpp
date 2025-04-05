//
// Created by artem on 07.04.2025.
//

#include "DicesBalatro.h"

DicesBalatro::DicesBalatro() {}

void DicesBalatro::setTexture(sf::Texture* texture) {
    if (texture) {
        sprite.setTexture(*texture);
    }
}

void DicesBalatro::setPosition (float x, float y) {
    sprite.setPosition(x, y);
}

void DicesBalatro::setScale(float scalex, float scaley) {
    sprite.setScale(scalex, scaley);
}

void DicesBalatro::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect DicesBalatro::getBounds() {
    return sprite.getGlobalBounds();
}
