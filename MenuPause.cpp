//
// Created by artem on 03.04.2025.
//

#include "MenuPause.h"

#include "GameMenu.h"
#include "MenuBalatro.h"

PauseMenu::PauseMenu(const sf::Font& font, const sf::Vector2u& windowSize) : visible(false) {
    background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    background.setFillColor(sf::Color(0, 0, 0, 180));

    resumeText.setFont(font);
    resumeText.setString("Resume Game");
    resumeText.setCharacterSize(40);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setPosition(windowSize.x / 2.f - 100, windowSize.y / 2.f - 100);

    saveText.setFont(font);
    saveText.setString("Save Game");
    saveText.setCharacterSize(40);
    saveText.setFillColor(sf::Color::White);
    saveText.setPosition(windowSize.x / 2.f - 100, windowSize.y / 2.f);

    settingsText.setFont(font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(40);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setPosition(windowSize.x / 2.f - 100, windowSize.y / 2.f + 100);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(40);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(windowSize.x / 2.f - 100, windowSize.y / 2.f + 200);
}

void PauseMenu::draw(sf::RenderWindow& window) {
    if (!visible) return;
    window.draw(background);
    window.draw(resumeText);
    window.draw(saveText);
    window.draw(settingsText);
    window.draw(exitText);
}

void PauseMenu::handleEvent(sf::Event& event, sf::RenderWindow& window, bool& resumeGame, bool& openSettings, bool& saveGame, bool& exitGame) {
    if (!visible) return;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (resumeText.getGlobalBounds().contains(mousePos)) {
            resumeGame = true;
            close();
        } else if (saveText.getGlobalBounds().contains(mousePos)) {
            saveGame = true;
        } else if (settingsText.getGlobalBounds().contains(mousePos)) {
            openSettings = true;
        } else if (exitText.getGlobalBounds().contains(mousePos)) {
            exitGame = true;
            window.clear(sf::Color::White);
            MenuBalatro(window);
        }
    }
}

bool PauseMenu::isOpen() const {
    return visible;
}

void PauseMenu::open() {
    visible = true;
}

void PauseMenu::close() {
    visible = false;
}

