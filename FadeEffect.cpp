//
// Created by artem on 03.04.2025.
//

#include "FadeEffect.h"

void FadeEffect::fadeIn(sf::RenderWindow& window, const std::vector<sf::Drawable*>& drawables, float duration) {
    sf::RectangleShape fadeRect(sf::Vector2f(window.getSize()));
    fadeRect.setFillColor(sf::Color(0, 0, 0, 255));

    sf::Clock clock;
    while (fadeRect.getFillColor().a > 0) {
        float progress = clock.getElapsedTime().asSeconds() / duration;
        progress = std::min(progress, 1.f);
        sf::Uint8 alpha = static_cast<sf::Uint8>(255 * (1.f - progress));
        fadeRect.setFillColor(sf::Color(0, 0, 0, alpha));

        window.clear();
        for (auto drawable : drawables) {
            window.draw(*drawable);
        }
        window.draw(fadeRect);
        window.display();
    }
}

void FadeEffect::fadeOut(sf::RenderWindow& window, const std::vector<sf::Drawable*>& drawables) {
    sf::RectangleShape fadeRect(sf::Vector2f(window.getSize()));
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));

    sf::Clock clock;
    float duration = 1.0f;

    while (fadeRect.getFillColor().a < 255) {
        float progress = clock.getElapsedTime().asSeconds() / duration;
        progress = std::min(progress, 1.f);
        fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(255 * progress)));

        window.clear();
        for (auto drawable : drawables)
            window.draw(*drawable);
        window.draw(fadeRect);
        window.display();
    }
}

bool FadeEffect::fading = false;
float FadeEffect::alpha = 0;
sf::RectangleShape FadeEffect::fadeRect;
sf::Clock FadeEffect::fadeClock;

void FadeEffect::startFadeOut(sf::RenderWindow& window) {
    fading = true;
    alpha = 0;
    fadeClock.restart();
    fadeRect.setSize(sf::Vector2f(window.getSize()));
    fadeRect.setFillColor(sf::Color(0, 0, 0, 0));
}

void FadeEffect::updateFadeOut(sf::RenderWindow& window) {
    if (!fading) return;

    float deltaTime = fadeClock.restart().asSeconds();
    alpha += 200.f * deltaTime;

    if (alpha >= 255) {
        alpha = 255;
        fading = false;
    }

    fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));
    window.draw(fadeRect);
}

bool FadeEffect::isFadeOutFinished() {
    return !fading && alpha >= 255;
}