#include "MenuPause.h"
#include "GameMenu.h"
#include "MenuBalatro.h"
#include "AudioManager.h"
#include "RectangleHover.h"

PauseMenu::PauseMenu(const sf::Font& fontRef, const sf::Vector2u& windowSize)
    : visible(false), visibleExit(false), font(&fontRef) {

    background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    background.setFillColor(sf::Color(0, 0, 0, 200));

    resumeText.setFont(*font);
    resumeText.setString("Resume Game");
    resumeText.setCharacterSize(40);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setPosition(windowSize.x / 2.f - 100, windowSize.y / 2.f - 100);

    saveText.setFont(*font);
    saveText.setString("Save Game");
    saveText.setCharacterSize(40);
    saveText.setFillColor(sf::Color::White);
    saveText.setPosition(windowSize.x / 2.f - 80, windowSize.y / 2.f);

    settingsText.setFont(*font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(40);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setPosition(windowSize.x / 2.f - 70, windowSize.y / 2.f + 100);

    exitText.setFont(*font);
    exitText.setString("Exit");
    exitText.setCharacterSize(40);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(windowSize.x / 2.f - 45, windowSize.y / 2.f + 200);
}

void PauseMenu::draw(sf::RenderWindow& window) {
    if (!visible) return;

    window.draw(background);
    window.draw(resumeText);
    window.draw(saveText);
    window.draw(settingsText);
    window.draw(exitText);
}

void PauseMenu::exitMenu(const sf::RenderWindow& window) {
    visibleExit = true;

    sf::Vector2f center(window.getSize().x / 2.f, window.getSize().y / 2.f);

    backgroundExit.setSize({400, 200});
    backgroundExit.setFillColor(sf::Color(50, 50, 50, 220));
    backgroundExit.setOutlineThickness(2);
    backgroundExit.setOutlineColor(sf::Color::White);
    backgroundExit.setOrigin(backgroundExit.getSize() / 2.f);
    backgroundExit.setPosition(center);

    promptText.setFont(*font);
    promptText.setString("ARE YOU SURE????");
    promptText.setCharacterSize(60);
    promptText.setFillColor(sf::Color::White);
    promptText.setPosition(center.x - 170, center.y - 50);

    okButton.setSize({80, 40});
    okButton.setFillColor(sf::Color(100, 100, 100));
    okButton.setPosition(center.x + 100, center.y + 80);

    okText.setFont(*font);
    okText.setString("OK");
    okText.setCharacterSize(20);
    okText.setFillColor(sf::Color::White);
    okText.setPosition(okButton.getPosition().x + 20, okButton.getPosition().y + 5);

    backButton.setSize({80, 40});
    backButton.setFillColor(sf::Color(100, 100, 100));
    backButton.setPosition(center.x - 100, center.y + 80);

    backText.setFont(*font);
    backText.setString("BACK");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(backButton.getPosition().x + 10, backButton.getPosition().y + 5);
}

void PauseMenu::exitDraw(sf::RenderWindow& window) {
    if (!visibleExit) return;

    window.draw(backgroundExit);
    window.draw(promptText);
    window.draw(okButton);
    window.draw(okText);
    window.draw(backButton);
    window.draw(backText);
}

void PauseMenu::handleEventExit(const sf::Event& event, sf::RenderWindow& window) {
    if (!visibleExit) return;

    RectangleHover::applyHoverEffect(okButton, window, true);
    RectangleHover::applyHoverEffect(backButton, window, true);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

        if (okButton.getGlobalBounds().contains(mouse)) {
            AudioManager::playClick();
            visibleExit = false;
            window.close();
        } else if (backButton.getGlobalBounds().contains(mouse)) {
            AudioManager::playClick();
            visibleExit = false;
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            AudioManager::playClick();
            visibleExit = false;
            window.close();
        } else if (event.key.code == sf::Keyboard::Escape) {
            AudioManager::playClick();
            visibleExit = false;
        }
    }
}

void PauseMenu::handleEvent(sf::Event& event, sf::RenderWindow& window,
                            bool& resumeGame, bool& openSettings,
                            bool& saveGame, bool& exitGame) {
    if (!visible) return;

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (resumeText.getGlobalBounds().contains(mousePos)) {
            resumeGame = true;
            close();
        } else if (saveText.getGlobalBounds().contains(mousePos)) {
            saveGame = true;
        } else if (settingsText.getGlobalBounds().contains(mousePos)) {
            openSettings = true;
        } else if (exitText.getGlobalBounds().contains(mousePos)) {
            exitMenu(window);
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
