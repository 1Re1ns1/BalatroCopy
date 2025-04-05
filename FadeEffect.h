//
// Created by artem on 03.04.2025.
//

#ifndef FADEEFFECT_H
#define FADEEFFECT_H



#include <SFML/Graphics.hpp>
#include <vector>

class FadeEffect {
public:
    static void fadeIn(sf::RenderWindow& window, const std::vector<sf::Drawable*>& drawables, float duration = 1.5f);
    static void fadeOut(sf::RenderWindow& window, const std::vector<sf::Drawable*>& drawables);
    static void startFadeOut(sf::RenderWindow& window);
    static void updateFadeOut(sf::RenderWindow& window);
    static bool isFadeOutFinished();
private:
    static bool fading;
    static float alpha;
    static sf::RectangleShape fadeRect;
    static sf::Clock fadeClock;
};


#endif //FADEEFFECT_H
