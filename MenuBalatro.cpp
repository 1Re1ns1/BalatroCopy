
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MenuBalatro.h"
#include "GameMenu.h"
#include "TextInput.h"
#include <iostream>
#include <unordered_map>
#include "HadeMenu.h"
#include "SettingsMenu.h"
#include "AudioManager.h"
#include <cmath>
#include "VolumeSlider.h"

// Новые подключенные классы
#include "TitleLetters.h"
#include "RectangleHover.h"
#include "TextAnimator.h"
#include "ExitPopup.h"
#include "NamePopup.h"
#include "SwayText.h"

TextAnimator animator;
ExitPopup exitPopup;
NamePopup namePopup;

void MenuBalatro(sf::RenderWindow& window) {
    sf::Cursor customCursor;
    sf::Image cursorImage;

    if (cursorImage.loadFromFile("Textures2/cursor.png")) {
        if (customCursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0))) {
            window.setMouseCursor(customCursor);
        } else {
            std::cerr << "Не удалось загрузить курсор из изображения" << std::endl;
        }
    } else {
        std::cerr << "Не удалось загрузить изображение курсора" << std::endl;
    }
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Pictures/backgroundMenu.png")) return;

    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    sf::Font font;
    if (!font.loadFromFile("Fonts/m6x11plus.ttf")) return;
    TitleLetters titleLetters("Gra kosciana", font, sf::Vector2f(window.getSize().x / 4.f + 75.f, window.getSize().y / 4.f - 150.f), 250.f);
    exitPopup.init(font, window);
    namePopup.init(font, window.getSize());

    sf::Text titleStart = TextAnimator::createText("Start", font, 100, sf::Color::White);
    sf::Text titleStartOutline = TextAnimator::createText("Start", font, 100, sf::Color::Black);

    sf::Text titleSettings = TextAnimator::createText("Settings", font, 100, sf::Color::White);
    sf::Text titleSettingsOutline = TextAnimator::createText("Settings", font, 100, sf::Color::Black);

    sf::Text titleExit = TextAnimator::createText("Exit", font, 100, sf::Color::White);
    sf::Text titleExitOutline = TextAnimator::createText("Exit", font, 100, sf::Color::Black);

    titleStart.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    titleStartOutline.setPosition(titleStart.getPosition());

    titleSettings.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 130.f);
    titleSettingsOutline.setPosition(titleSettings.getPosition());

    titleExit.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 260.f);
    titleExitOutline.setPosition(titleExit.getPosition());

    SwayText2 swayStart(titleStart, titleStart.getPosition());
    SwayText2 swayStartOutline(titleStartOutline, titleStart.getPosition());
    SwayText1 swaySettings(titleSettings, titleSettings.getPosition());
    SwayText1 swaySettingsOutline(titleSettingsOutline, titleSettingsOutline.getPosition());
    SwayText2 swayExit(titleExit, titleExit.getPosition());
    SwayText2 swayExitOutline(titleExitOutline, titleExit.getPosition());
    AudioManager::init();

    std::string playerName = "";
    bool showNamePopup = false;
    bool showBackPopup = false;

    sf::Text version;
    version.setFont(font);
    version.setString("version: alpha1");
    version.setCharacterSize(25);
    version.setFillColor(sf::Color::White);
    version.setStyle(sf::Text::Bold);
    version.setPosition(10, window.getSize().y - 30);
    bool shouldExit = false;
    sf::Clock swayClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (showNamePopup)
                namePopup.handleEvent(event, window, showNamePopup, playerName, {
        &backgroundSprite,
        &titleStart, &titleStartOutline,
        &titleSettings, &titleSettingsOutline,
        &titleExit, &titleExitOutline,
        &version,&titleLetters,
        &namePopup.background,
        &namePopup.promptText,
        &namePopup.inputText, &namePopup.okText,
        &namePopup.backButton, &namePopup.backText,
        &namePopup.okButton, &namePopup.okText, &namePopup.inputText, &namePopup.inputBox
    });

            if (showBackPopup)
                exitPopup.handleEvent(event, window, shouldExit, showBackPopup, {
    &backgroundSprite,
    &titleStart, &titleStartOutline,
    &titleSettings, &titleSettingsOutline,
    &titleExit, &titleExitOutline,
    &version,&titleLetters,
    &exitPopup.background,
    &exitPopup.promptText,
    &exitPopup.okButton, &exitPopup.okText,
    &exitPopup.backButton, &exitPopup.backText
});

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (titleStart.getGlobalBounds().contains(mouse)) {
                    AudioManager::playClick();
                    playerName.clear();
                    namePopup.show();
                    showNamePopup = true;
                } else if (titleSettings.getGlobalBounds().contains(mouse)) {
                    AudioManager::playClick();
                    SettingsMenu(window);
                } else if (titleExit.getGlobalBounds().contains(mouse)) {
                    AudioManager::playClick();
                    exitPopup.show();
                    showBackPopup = true;
                }
            }

            TextAnimator::applyHoverEffect(titleStart, titleStartOutline, window);
            TextAnimator::applyHoverEffect(titleSettings, titleSettingsOutline, window);
            TextAnimator::applyHoverEffect(titleExit, titleExitOutline, window);
        }

        sf::Clock clock;
        float deltaTime = clock.restart().asSeconds();
        titleLetters.update(deltaTime);
        float swayOffset = std::sin(swayClock.getElapsedTime().asSeconds() * 2.f) * 5.f;
        float swayTime = swayClock.getElapsedTime().asSeconds();
        swayStart.update(swayTime);
        swaySettings.update(swayTime);
        swayExit.update(swayTime);
        window.clear();
        window.draw(backgroundSprite);
        titleLetters.update(swayOffset);
        window.draw(titleLetters);
        TextAnimator::drawWithOutline(window, titleStart, titleStartOutline);
        TextAnimator::drawWithOutline(window, titleSettings, titleSettingsOutline);
        TextAnimator::drawWithOutline(window, titleExit, titleExitOutline);
        window.draw(version);

        if (showNamePopup) namePopup.draw(window);
        if (showBackPopup) exitPopup.draw(window);

        window.display();
    }
}