//
// Created by artem on 07.04.2025.
//

#ifndef DICESBALATRO_H
#define DICESBALATRO_H
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics.hpp"



class DicesBalatro {
public:
    DicesBalatro();


    void setTexture(sf::Texture* texture);
    void setPosition (float x, float y);
    void init(const sf::RenderWindow& window);
    void setScale(float scalex, float scaley);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    sf::Sprite sprite;
};



#endif //DICESBALATRO_H
