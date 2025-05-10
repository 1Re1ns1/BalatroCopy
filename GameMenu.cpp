#include <SFML/Graphics.hpp>
#include "GameMenu.h"
#include "TextInput.h"
#include <iostream>
#include "MenuPause.h"
#include "SettingsMenu.h"
#include "RectangleHover.h"
#include <string>
#include "DicesBalatro.h"
#include "SwayText.h"
#include "TextAnimator.h"

sf::RectangleShape tabBackground;
sf::RectangleShape helpMenuBackground;
sf::Text helpTitle;
std::vector<sf::Text> helpItems;
bool showPauseMenu = false;
sf::Text rerollInfo;
sf::Text allrerollInfo;

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

void InitRulesMenu(sf::Font& font, sf::RenderWindow& window) {
    helpMenuBackground.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    helpMenuBackground.setFillColor(sf::Color(0, 0, 0, 150));
    helpMenuBackground.setPosition(0, 0);

    helpTitle.setFont(font);
    helpTitle.setString("Combinations");
    helpTitle.setCharacterSize(28);
    helpTitle.setFillColor(sf::Color::White);
    helpTitle.setPosition(20, 20);

    helpTitle.setFont(font);
    helpTitle.setString("Zasady gry");
    helpTitle.setCharacterSize(36);
    helpTitle.setFillColor(sf::Color::White);
    helpTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
    helpTitle.setPosition(window.getSize().x / 2.f - helpTitle.getGlobalBounds().width / 2.f, 20);

    std::vector<std::string> rules = {
        "- Aby wygrać rundę, gracz musi zdobyć więcej punktów niż komputer.",
        "- Klikając lewym przyciskiem myszy na kość, można ją przerzucić (maksymalnie 3 razy w sumie).",
        "- Naciśnięcie klawisza R przerzuca wszystkie kości, ale tylko raz.",
        "- W jednej grze można odkryć tylko 2 kości przeciwnika."
    };

    float y = window.getSize().y/2.f;
    for (const std::string& text : rules) {
        sf::Text item;
        item.setFont(font);
        item.setString(text);
        item.setCharacterSize(22);
        item.setFillColor(sf::Color::White);
        item.setPosition(window.getSize().x / 2.f - 280.f, y);
        y += 50;

        helpItems.push_back(item);
    }
}

void DrawRulesMenu(sf::RenderWindow& window) {
    window.draw(helpMenuBackground);
    window.draw(helpTitle);
    for (auto& item : helpItems) {
        window.draw(item);
    }
}

void UpdateRerollTexts(int totalRerolls, int allRerolls, sf::Font& font, sf::RenderWindow& window) {
    rerollInfo.setFont(font);
    rerollInfo.setCharacterSize(20);
    rerollInfo.setFillColor(sf::Color::Yellow);
    rerollInfo.setString("Pozostale przerzuty: " + std::to_string(totalRerolls));
    rerollInfo.setPosition(window.getSize().x - 300, 40);

    allrerollInfo.setFont(font);
    allrerollInfo.setCharacterSize(20);
    allrerollInfo.setFillColor(sf::Color::Cyan);
    allrerollInfo.setString("Przerzut wszystkich: " + std::to_string(allRerolls));
    allrerollInfo.setPosition(window.getSize().x - 300, 70);
}

void GameMenu(sf::RenderWindow& window) {
    std::vector<sf::Texture> diceTextures;
    std::vector<sf::Texture> noTextures;
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


    diceTextures.resize(6);
    for (int i = 0; i < 6; ++i) {
        std::string path = "Texture/Dice" + std::to_string(i + 1) + ".png";
        if (!diceTextures[i].loadFromFile(path)) {
            std::cerr << "Failed to load: " << path << std::endl;
        }
    }
    noTextures.resize(6);
    for (int i = 0; i < 6; ++i) {
        std::string path = "Textures2/Dice Komputer.png";
        bool ok = noTextures[i].loadFromFile(path);
        std::cout << "Load " << path << ": " << std::boolalpha << ok << "\n";
    }
    sf::Text titleMenu = TextAnimator::createText("Menu", font, 100, sf::Color::White);
    sf::Text titleMenuOutline = TextAnimator::createText("Menu", font, 100, sf::Color::Black);

    titleMenu.setPosition(window.getSize().x / 10.f, window.getSize().y / 10.f);
    titleMenuOutline.setPosition(titleMenu.getPosition());

    SwayText2 swayMenu(titleMenu, titleMenu.getPosition());
    SwayText2 swayMenuOutline(titleMenuOutline, titleMenu.getPosition());

    sf::Text titleTab = TextAnimator::createText("Combinations", font, 60, sf::Color::White);
    sf::Text titleTabOutline = TextAnimator::createText("Combinations", font, 60, sf::Color::Black);

    titleTab.setPosition(window.getSize().x / 10.f, window.getSize().y / 5.f);
    titleTabOutline.setPosition(titleTab.getPosition());

    SwayText1 swayTab(titleTab, titleTab.getPosition());
    SwayText1 swayTabOutline(titleTabOutline, titleTab.getPosition());

    sf::Text titleScore = TextAnimator::createText("Score:", font, 70, sf::Color::White);
    sf::Text titleScoreOutline = TextAnimator::createText("Score:", font, 70, sf::Color::Black);

    titleScore.setPosition(window.getSize().x / 11.f, window.getSize().y / 3.f);
    titleScoreOutline.setPosition(titleScore.getPosition());

    SwayText2 swayScore(titleScore, titleScore.getPosition());
    SwayText2 swayScoreOutline(titleScoreOutline, titleScore.getPosition());

    sf::Text titleRules = TextAnimator::createText("rules", font, 60, sf::Color::White);
    sf::Text titleRulesOutline = TextAnimator::createText("rules", font, 60, sf::Color::Black);

    titleRules.setPosition(window.getSize().x / 10.f, window.getSize().y / 1.1);
    titleRulesOutline.setPosition(titleRules.getPosition());

    SwayText1 swayRules(titleRules, titleRules.getPosition());
    SwayText1 swayRulesOutline(titleRulesOutline, titleRules.getPosition());

    std::vector<DicesBalatro> diceSprites = DicesBalatro::generateDiceSet(5, diceTextures, window, DiceRow::Bottom);
    std::vector<DicesBalatro> diceComputer = DicesBalatro::generateDiceSet(5, diceTextures, window, DiceRow::Top);
    std::vector<DicesBalatro> noComputer = DicesBalatro::generateDiceSet(5, noTextures, window, DiceRow::Top);
    sf::Vector2f rectSize(250.f, 60.f);


    sf::RectangleShape leftPanel;
    leftPanel.setSize(sf::Vector2f(window.getSize().x / 5.f, window.getSize().y));
    leftPanel.setFillColor(sf::Color(30, 30, 30, 200));
    leftPanel.setPosition(0.f, 0.f);
    leftPanel.setOutlineThickness(2);
    leftPanel.setOutlineColor(sf::Color::White);

    sf::RectangleShape downPanel;
    downPanel.setSize(sf::Vector2f(window.getSize().x, window.getSize().y / 5.f));
    downPanel.setFillColor(sf::Color(30, 30, 30, 200));
    downPanel.setPosition(0.f+ leftPanel.getSize().x, window.getSize().y - downPanel.getSize().y);
    downPanel.setOutlineThickness(2);
    downPanel.setOutlineColor(sf::Color::White);

    sf::RectangleShape topPanel;
    topPanel.setSize(sf::Vector2f(window.getSize().x, window.getSize().y / 5.f));
    topPanel.setFillColor(sf::Color(30, 30, 30, 200));
    topPanel.setPosition(0.f+ leftPanel.getSize().x, 0.f);
    topPanel.setOutlineThickness(2);
    topPanel.setOutlineColor(sf::Color::White);


    bool showHelpMenu = false;
    bool fadefinished = false;
    PauseMenu pauseMenu(font, window.getSize());

    bool gamePaused = false;
    bool resumeGame = false;
    bool openSettings = false;
    bool saveGame = false;
    bool exitGame = false;
    bool gameRules = false;
    sf::Clock swayClock;
    int totalRerolls = 3;
    int allReroles = 1;

    while (window.isOpen()) {
        sf::Event event;
        for (size_t i=0; i < diceSprites.size(); ++i) {
            diceSprites[i].handelEvent(event, window, i);
        }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            HandleTextInput(event);

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y) {
                gameRules = !gameRules;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (titleMenu.getGlobalBounds().contains(mouse)) {
                    AudioManager::playClick();
                    gamePaused = !gamePaused;
                    if (gamePaused) pauseMenu.open();
                    else pauseMenu.close();
                } else if (titleTab.getGlobalBounds().contains(mouse)) {
                    AudioManager::playClick();
                    showHelpMenu = !showHelpMenu;
                } else if (titleRules.getGlobalBounds().contains(mouse)) {
                    AudioManager::playClick();
                    gameRules = !gameRules;
                }
                if (showHelpMenu && !helpMenuBackground.getGlobalBounds().contains(mouse)) {
                showHelpMenu = false;
                AudioManager::playClick();
                }
                if (totalRerolls > 0) {
                    for (auto& dice : diceSprites) {
                        if (dice.getSprite()->getGlobalBounds().contains(mouse)) {
                            dice.reroll(diceTextures);
                            totalRerolls--;
                            break;
                        }
                    }
                }
            }
            if (gamePaused) {
                pauseMenu.handleEventExit(event, window);
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
            if (allReroles > 0) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    DicesBalatro::rerollDiceSet(diceSprites, diceTextures);
                    allReroles--;
                }
            }
            TextAnimator::applyHoverEffect(titleMenu, titleMenuOutline, window);
            TextAnimator::applyHoverEffect(titleTab, titleTabOutline, window);
            TextAnimator::applyHoverEffect(titleRules, titleRulesOutline, window);
        }

        if (!fadefinished) {
            fadefinished = true;
            FadeEffect::fadeIn(window, {&backgroundSprite, diceSprites[0].getSprite(),
            diceSprites[1].getSprite()}, 1);
        }

        UpdateRerollTexts(totalRerolls, allReroles, font, window);
        int score = DicesBalatro::calculateDiceScore(diceSprites, diceTextures);
        int lastDiceScore = score;  // сохранить глобально или передать куда нужно
        std::cout << score << std::endl;
        titleScore.setString("Score: " + std::to_string(score));
        float swayTime = swayClock.getElapsedTime().asSeconds();
        window.clear();
        window.draw(backgroundSprite);
        window.draw(leftPanel);
        window.draw(downPanel);
        window.draw(topPanel);
        swayMenu.update(swayTime);
        swayTab.update(swayTime);
        swayScore.update(swayTime);
        swayRules.update(swayTime);
        window.draw(rerollInfo);
        window.draw(allrerollInfo);
        TextAnimator::drawWithOutline(window, titleMenu, titleMenuOutline);
        TextAnimator::drawWithOutline(window, titleTab, titleTabOutline);
        TextAnimator::drawWithOutline(window, titleScore, titleScoreOutline);
        TextAnimator::drawWithOutline(window, titleRules, titleRulesOutline);
        for (auto& dice : diceSprites) {
            dice.draw(window);
        }
        for (auto& dice : diceComputer) {
            dice.draw(window); // верхний ряд
        }
        for (auto& clone : noComputer) {
            clone.draw(window); // верхний ряд
        }
        if (showHelpMenu) {
            InitHelpMenu(font, window);
            DrawHelpMenu(window);
        }
        if (gamePaused) {
            pauseMenu.draw(window);
            pauseMenu.exitDraw(window);
        }
        if (gameRules) {
            InitRulesMenu(font, window);
            DrawRulesMenu(window);
        }
        window.display();
    }
}