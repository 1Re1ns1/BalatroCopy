#include <SFML/Graphics.hpp>
#include "GameMenu.h"
#include "TextInput.h"
#include <iostream>
#include "MenuPause.h"
#include "SettingsMenu.h"
#include "RectangleHover.h"

sf::RectangleShape tabBackground;
sf::RectangleShape helpMenuBackground;
sf::Text helpTitle;
std::vector<sf::Text> helpItems;
bool showPauseMenu = false;

void InitHelpMenu(sf::Font& font, sf::RenderWindow& window) {
    helpMenuBackground.setSize(sf::Vector2f(400, window.getSize().y));
    helpMenuBackground.setFillColor(sf::Color(0, 0, 0, 150));
    helpMenuBackground.setPosition(0, 0);

    helpTitle.setFont(font);
    helpTitle.setString("Combinations");
    helpTitle.setCharacterSize(28);
    helpTitle.setFillColor(sf::Color::White);
    helpTitle.setPosition(20, 20);

    std::vector<std::string> combinations = {
        "Pair: Two same dice",
        "Three of a kind: Three same dice",
        "Straight: 1-2-3-4-5 or 2-3-4-5-6",
        "Full House: Pair + Three of a kind",
        "Four of a kind: Four same dice",
        "Five of a kind: All dice same",
        "Yahtzee Combo: Special roll"
    };

    float y = 70;
    for (const std::string& text : combinations) {
        sf::Text item;
        item.setFont(font);
        item.setString("- " + text);
        item.setCharacterSize(20);
        item.setFillColor(sf::Color::White);
        item.setPosition(20, y);
        y += 40;
        helpItems.push_back(item);
    }
}

void DrawHelpMenu(sf::RenderWindow& window) {
    window.draw(helpMenuBackground);
    window.draw(helpTitle);
    for (auto& item : helpItems) {
        window.draw(item);
    }
}

void FadeIn(sf::RenderWindow& window, sf::Sprite& backgroundSprite, sf::RectangleShape& startButton, sf::RectangleShape& settingsButton, sf::RectangleShape& backButton, sf::Text& title) {
    sf::RectangleShape fadeRect(sf::Vector2f(window.getSize()));
    fadeRect.setFillColor(sf::Color(0, 0, 0, 255));

    sf::Clock fadeClock;
    float duration = 1.5f;

    while (fadeRect.getFillColor().a > 0) {
        float progress = fadeClock.getElapsedTime().asSeconds() / duration;
        progress = std::min(progress, 1.f);
        sf::Uint8 alpha = static_cast<sf::Uint8>(255 * (1.f - progress));
        fadeRect.setFillColor(sf::Color(0, 0, 0, alpha));

        window.clear();
        window.draw(backgroundSprite);
        window.draw(startButton);
        window.draw(settingsButton);
        window.draw(title);
        window.draw(backButton);
        window.draw(fadeRect);
        window.display();
    }
}

void GameMenu(sf::RenderWindow& window) {
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Pictures/backgroundgame.jpg")) {
        std::cerr << "Error download" << std::endl;
        return;
    }

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("Pictures/buttontexture.jpg")) {
        std::cerr << "Error download" << std::endl;
        return;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    sf::Font font;
    if (!font.loadFromFile("Fonts/m6x11plus.ttf")) {
        std::cerr << "Error download" << std::endl;
        return;
    }

    sf::Vector2f rectSize(250.f, 60.f);

    sf::RectangleShape startButton(rectSize);
    startButton.setTexture(&buttonTexture);
    startButton.setPosition(window.getSize().x / 3 - rectSize.x / 2, window.getSize().y / 1.5);

    sf::RectangleShape settingsButton(rectSize);
    settingsButton.setTexture(&buttonTexture);
    settingsButton.setPosition(window.getSize().x / 2 - rectSize.x / 2, window.getSize().y / 1.5);

    sf::RectangleShape backButton(rectSize);
    backButton.setTexture(&buttonTexture);
    backButton.setPosition(window.getSize().x / 1.5 - rectSize.x / 2, window.getSize().y / 1.5);

    sf::Text title;
    title.setFont(font);
    title.setString("Game Menu");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Blue);
    title.setStyle(sf::Text::Bold);
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.width / 2, textRect.height / 2);
    title.setPosition(window.getSize().x / 2, window.getSize().y / 6);

    bool showHelpMenu = false;
    bool fadefinished = false;
    PauseMenu pauseMenu(font, window.getSize());

    bool gamePaused = false;
    bool resumeGame = false;
    bool openSettings = false;
    bool saveGame = false;
    bool exitGame = false;

    while (window.isOpen()) {
        sf::Event event;

        RectangleHover::applyHoverEffect(startButton, window, true);
        RectangleHover::applyHoverEffect(settingsButton, window, true);
        RectangleHover::applyHoverEffect(backButton, window, true);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            HandleTextInput(event);

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                        return;
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab) {
                showHelpMenu = !showHelpMenu;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                gamePaused = !gamePaused;
                if (gamePaused) pauseMenu.open();
                else pauseMenu.close();
            }

            if (gamePaused) {
                pauseMenu.handleEvent(event, window, resumeGame, openSettings, saveGame, exitGame);
            }

            if (resumeGame) {
                gamePaused = false;
                resumeGame = false;
            }

            if (openSettings) {
                SettingsMenu(window);
                openSettings = false;
            }

            if (saveGame) {
                std::cout << "Game saved!\n";
                saveGame = false;
            }
        }

        if (!fadefinished) {
            fadefinished = true;
            FadeIn(window, backgroundSprite, startButton, settingsButton, backButton, title);
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        window.draw(startButton);
        window.draw(settingsButton);
        window.draw(backButton);

        if (showHelpMenu) {
            InitHelpMenu(font, window);
            DrawHelpMenu(window);
        }
        if (gamePaused) {
            pauseMenu.draw(window);
        }
        window.display();
    }
}
