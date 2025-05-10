//
// Created by artem on 07.04.2025.
//

#ifndef DICESBALATRO_H
#define DICESBALATRO_H
#include "SFML/Graphics.hpp"
#include "AudioManager.h"
#include "FadeEffect.h"
#include <numeric>
#include <algorithm>
#include <random>

enum class DiceRow {
    Top,
    Bottom
};

class DicesBalatro {
public:
    DicesBalatro();


    void setTexture(sf::Texture* texture);
    void setPosition (float x, float y);
    void init(const sf::RenderWindow& window);
    void setScale(float scalex, float scaley);
    void draw(sf::RenderWindow& window);
    void handelEvent(sf::Event& event, sf::RenderWindow& window, int index);
    void getPosition(sf::Sprite& sprite);
    sf::Sprite* getSprite() const;
    static std::vector<DicesBalatro> generateDiceSet(int count, const std::vector<sf::Texture>& textures, const sf::RenderWindow& window, DiceRow row);
    static void rerollDiceSet(std::vector<DicesBalatro>& diceSprites, const std::vector<sf::Texture>& textures);
    static int calculateDiceScore(const std::vector<DicesBalatro>& diceSprites, const std::vector<sf::Texture>& textures);
    void reroll(const std::vector<sf::Texture>& textures);


private:
    sf::FloatRect getBounds();
    sf::Sprite sprite;
    float posx, posy;
    float prevX, prevY;
    bool isMoved = false;
};


#endif //DICESBALATRO_H
