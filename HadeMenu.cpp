//
// Created by artem on 19.03.2025.
//

#include "HadeMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class FadeInScreen {
public:
    sf::RectangleShape overlay;
    sf::Text fadeText;
    sf::Text fadeText2;
    sf::Font font;
    float alpha;
    float alpha2;
    float alpha3;
    bool fading;
    bool showSecondText;

    FadeInScreen(sf::RenderWindow& window) {
        overlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 255)); // Черный экран с полной непрозрачностью

        if (!font.loadFromFile("Fonts/m6x11plus.ttf")) {
            std::cerr << "Error loading font" << std::endl;
        }

        fadeText.setFont(font);
        fadeText.setString("XZ");
        fadeText.setCharacterSize(250);
        fadeText.setFillColor(sf::Color(255, 255, 255, 255));
        fadeText.setPosition(
            window.getSize().x / 2 - fadeText.getLocalBounds().width / 2,
            window.getSize().y / 2 - fadeText.getLocalBounds().height / 2
        );

        fadeText2.setFont(font);
        fadeText2.setString("   Artem\n  Kyrylo\nOleksandr");
        fadeText2.setCharacterSize(250);
        fadeText2.setFillColor(sf::Color(255, 255, 255, 0)); // Начально невидимый
        fadeText2.setPosition(
            window.getSize().x / 2 - fadeText2.getLocalBounds().width / 2,
            window.getSize().y / 2 - fadeText2.getLocalBounds().height / 2
        );

        alpha = 255;
        alpha2 = 255;
        alpha3 = 0;
        fading = true;
        showSecondText = false;
    }

    void update() {
        if (fading) {
            if (alpha > 0) {
                alpha -= 0.05; // Скорость исчезновения первого текста
                fadeText.setFillColor(sf::Color(255, 255, 255, static_cast<int>(alpha)));
            } else if (!showSecondText) {
                showSecondText = true;
                alpha3 = 255; // Начинаем показывать второй текст
                fadeText2.setFillColor(sf::Color(255, 255, 255, static_cast<int>(alpha3)));
            }

            if (showSecondText && alpha3 > 0) {
                alpha3 -= 0.05; // Исчезновение второго текста
                fadeText2.setFillColor(sf::Color(255, 255, 255, static_cast<int>(alpha3)));
            }

            if (showSecondText && alpha3 <= 0) {
                fading = false; // Завершение анимации
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(overlay);
        if (alpha > 0) {
            window.draw(fadeText);
        } else if (showSecondText) {
            window.draw(fadeText2);
        }
    }
};


void HadeMenu(sf::RenderWindow& window) {
    FadeInScreen fadeEffect(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        fadeEffect.update();

        window.clear();
        fadeEffect.draw(window);
        window.display();

        if (!fadeEffect.fading) {
            break; // Выход после завершения анимации
        }
    }
}
