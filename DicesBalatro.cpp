#include "DicesBalatro.h"
#include "GameMenu.h"
#include <map>
#include <algorithm>
#include <iostream>

int lastDiceScore = 0;

DicesBalatro::DicesBalatro() {}

void DicesBalatro::setTexture(sf::Texture* texture) {
    if (texture) {
        sprite.setTexture(*texture);
    }
}

void DicesBalatro::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void DicesBalatro::getPosition(sf::Sprite& sprite) {
    posx = sprite.getPosition().x;
    posy = sprite.getPosition().y;
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

std::vector<DicesBalatro> DicesBalatro::generateDiceSet(
    int count,
    const std::vector<sf::Texture>& textures,
    const sf::RenderWindow& window,
    DiceRow row)
{
    std::vector<DicesBalatro> diceSprites;
    if (count > 6) count = 6;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(textures.size()) - 1);

    float spacing = 200.f;
    float totalWidth = spacing * (count - 1);
    float startX = window.getSize().x / 2.f - totalWidth / 2.f;
    float posY = (row == DiceRow::Top) ? 50.f : (window.getSize().y - 200.f);

    for (int i = 0; i < count; ++i) {
        DicesBalatro dice;
        int texIndex = dist(gen);
        dice.setTexture(const_cast<sf::Texture*>(&textures[texIndex]));
        dice.setPosition(startX + i * spacing, posY);
        dice.setScale(0.7f, 0.7f);
        diceSprites.push_back(dice);
    }

    return diceSprites;
}

void DicesBalatro::handelEvent(sf::Event& event, sf::RenderWindow& window, int index) {
    bool reacted = true;
    float x, y;
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
        sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
        if (sprite.getGlobalBounds().contains(mouse)) {
            AudioManager::playClick();

            if (!isMoved) {
                prevX = sprite.getPosition().x;
                prevY = sprite.getPosition().y;
                sprite.setPosition(window.getSize().x / 2 + 200.f * index, window.getSize().y / 2);
                isMoved = true;
            } else {
                sprite.setPosition(prevX, prevY);
                isMoved = false;
            }
        }
    }
}

void DicesBalatro::rerollDiceSet(std::vector<DicesBalatro>& diceSprites, const std::vector<sf::Texture>& textures) {
    if (textures.empty()) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(textures.size()) - 1);

    for (int i = 0; i < diceSprites.size(); ++i) {
        int texIndex = dist(gen);
        diceSprites[i].setTexture(const_cast<sf::Texture*>(&textures[texIndex]));
    }
}

int DicesBalatro::calculateDiceScore(const std::vector<DicesBalatro>& diceSprites, const std::vector<sf::Texture>& textures) {
    std::map<int, int> valueCount;
    std::vector<int> values;

    for (auto& dice : diceSprites) {
        int value = 0;
        for (size_t i = 0; i < textures.size(); ++i) {
            if (&textures[i] == dice.getSprite()->getTexture()) {
                value = static_cast<int>(i) + 1;
                break;
            }
        }
        values.push_back(value);
        valueCount[value]++;
    }

    std::sort(values.begin(), values.end());

    bool isStraight = (values == std::vector<int>{1,2,3,4,5} || values == std::vector<int>{2,3,4,5,6});
    bool hasPair = false, hasThree = false, hasFour = false, hasFive = false;
    int score = 0;

    for (const auto& [val, count] : valueCount) {
        if (count == 2) hasPair = true;
        if (count == 3) hasThree = true;
        if (count == 4) hasFour = true;
        if (count == 5) hasFive = true;
    }

    if (hasFive) {
        score = 50;
    } else if (hasFour) {
        score = 40;
    } else if (hasThree && hasPair) {
        score = 35;
    } else if (isStraight) {
        score = 30;
    } else if (hasThree) {
        score = 25;
    } else if (hasPair) {
        score = 10;
    }
    return score;
}

sf::Sprite* DicesBalatro::getSprite() const {
    return const_cast<sf::Sprite*>(&sprite);
}

void DicesBalatro::reroll(const std::vector<sf::Texture>& textures) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(textures.size()) - 1);
    int texIndex = dist(gen);
    setTexture(const_cast<sf::Texture*>(&textures[texIndex]));
}
