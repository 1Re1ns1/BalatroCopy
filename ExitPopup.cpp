//
// Created by artem on 03.04.2025.
//

#include "ExitPopup.h"
#include "ExitPopup.h"
#include "AudioManager.h"
#include "RectangleHover.h"
#include "FadeEffect.h"

ExitPopup::ExitPopup() : visible(false) {}

void ExitPopup::init(sf::Font& font, const sf::RenderWindow& window) {
    sf::Vector2f center(window.getSize().x / 2.f, window.getSize().y / 2.f);

    background.setSize({400, 200});
    background.setFillColor(sf::Color(50, 50, 50, 220));
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::White);
    background.setOrigin(background.getSize() / 2.f);
    background.setPosition(center);

    promptText.setFont(font);
    promptText.setString("ARE YOU SURE????");
    promptText.setCharacterSize(60);
    promptText.setFillColor(sf::Color::White);
    promptText.setPosition(center.x - 170, center.y - 50);

    okButton.setSize({80, 40});
    okButton.setFillColor(sf::Color(100, 100, 100));
    okButton.setPosition(center.x + 100, center.y + 80);

    okText.setFont(font);
    okText.setString("OK");
    okText.setCharacterSize(20);
    okText.setFillColor(sf::Color::White);
    okText.setPosition(okButton.getPosition().x + 20, okButton.getPosition().y + 5);

    backButton.setSize({80, 40});
    backButton.setFillColor(sf::Color(100, 100, 100));
    backButton.setPosition(center.x, center.y + 80);

    backText.setFont(font);
    backText.setString("BACK");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(backButton.getPosition().x + 20, backButton.getPosition().y + 5);
}

void ExitPopup::draw(sf::RenderWindow& window) {
    if (!visible) return;
    window.draw(background);
    window.draw(promptText);
    window.draw(okButton);
    window.draw(okText);
    window.draw(backButton);
    window.draw(backText);
}

void ExitPopup::handleEvent(const sf::Event& event, sf::RenderWindow& window,
                            bool& shouldExit, bool& showBackPopup,
                            const std::vector<sf::Drawable*>& drawablesToFade) {
    if (!visible) return;

    RectangleHover::applyHoverEffect(okButton, window, true);
    RectangleHover::applyHoverEffect(backButton, window, true);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

        if (okButton.getGlobalBounds().contains(mouse)) {
            AudioManager::playClick();
            shouldExit = true;
            visible = false;

            FadeEffect::fadeOut(window, drawablesToFade); // <--- все вместе
            window.close();
        } else if (backButton.getGlobalBounds().contains(mouse)) {
            AudioManager::playClick();
            showBackPopup = false;
            visible = false;
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            AudioManager::playClick();
            shouldExit = true;
            visible = false;

            FadeEffect::fadeOut(window, drawablesToFade);
            window.close();
        } else if (event.key.code == sf::Keyboard::Escape) {
            AudioManager::playClick();
            showBackPopup = false;
            visible = false;
        }
    }
}

void ExitPopup::show() {
    visible = true;
}

void ExitPopup::hide() {
    visible = false;
}

bool ExitPopup::isVisible() const {
    return visible;
}