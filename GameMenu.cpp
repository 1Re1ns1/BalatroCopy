#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "GameMenu.h"
#include "TextInput.h"
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
int revealedEnemyDice = 0;
std::vector<bool> enemyDiceRevealed(5, true);
bool showResultPopup = false;
sf::RectangleShape popupBackground;
sf::Text popupText;
sf::RectangleShape popupOkButton;
sf::Text popupOkText;
bool popupVisible = false;

sf::RectangleShape finalPopupBackground;
sf::Text finalPopupText;
sf::Text finalPopupStats;
sf::RectangleShape finalPopupOkButton;
sf::Text finalPopupOkText;
bool finalPopupVisible = false;
int totalRounds = 0;
int totalWins = 0;
int totalLosses = 0;
int totalScorePlayer = 0;
int totalScoreComputer = 0;
bool allowInput = true;

void InitFinalPopup(const sf::Font& font, const sf::RenderWindow& window) {
    sf::Vector2f center(window.getSize().x / 2.f, window.getSize().y / 2.f);

    finalPopupBackground.setSize({500.f, 300.f});
    finalPopupBackground.setFillColor(sf::Color(50, 50, 50, 220));
    finalPopupBackground.setOutlineThickness(2.f);
    finalPopupBackground.setOutlineColor(sf::Color::White);
    finalPopupBackground.setOrigin(finalPopupBackground.getSize() / 2.f);
    finalPopupBackground.setPosition(center);

    finalPopupText.setFont(font);
    finalPopupText.setString("GAME OVER");
    finalPopupText.setCharacterSize(40);
    finalPopupText.setFillColor(sf::Color::White);
    finalPopupText.setPosition(center.x - 120.f, center.y - 100.f);

    std::string stats = "Rounds: 10\nWins: " + std::to_string(totalWins) +
                        "\nLosses: " + std::to_string(totalLosses) +
                        "\nPlayer Score: " + std::to_string(totalScorePlayer) +
                        "\nComputer Score: " + std::to_string(totalScoreComputer);

    finalPopupStats.setFont(font);
    finalPopupStats.setString(stats);
    finalPopupStats.setCharacterSize(22);
    finalPopupStats.setFillColor(sf::Color::White);
    finalPopupStats.setPosition(center.x - 180.f, center.y - 40.f);

    finalPopupOkButton.setSize({100.f, 40.f});
    finalPopupOkButton.setFillColor(sf::Color(100, 100, 100));
    finalPopupOkButton.setPosition(center.x - 50.f, center.y + 100.f);
    finalPopupOkButton.setOutlineThickness(2.f);
    finalPopupOkButton.setOutlineColor(sf::Color::White);

    finalPopupOkText.setFont(font);
    finalPopupOkText.setString("OK");
    finalPopupOkText.setCharacterSize(24);
    finalPopupOkText.setFillColor(sf::Color::White);
    finalPopupOkText.setPosition(finalPopupOkButton.getPosition().x + 30.f, finalPopupOkButton.getPosition().y + 5.f);

    finalPopupVisible = true;
    allowInput = false; // блокируем ввод
}

void InitResultPopup(const std::string& resultMessage, const sf::Font& font, const sf::RenderWindow& window) {
    sf::Vector2f center(window.getSize().x / 1.7, window.getSize().y / 2.f);

    popupBackground.setSize({400.f, 200.f});
    popupBackground.setFillColor(sf::Color(50, 50, 50, 220));
    popupBackground.setOutlineThickness(2.f);
    popupBackground.setOutlineColor(sf::Color::White);
    popupBackground.setOrigin(popupBackground.getSize() / 2.f);
    popupBackground.setPosition(center);

    popupText.setFont(font);
    popupText.setString(resultMessage);
    popupText.setCharacterSize(40);
    popupText.setFillColor(resultMessage == "YOU WIN" ? sf::Color::Green : sf::Color::Red);
    popupText.setPosition(center.x - 80.f, center.y - 40.f);

    popupOkButton.setSize({100.f, 40.f});
    popupOkButton.setFillColor(sf::Color(100, 100, 100));
    popupOkButton.setPosition(center.x - 50.f, center.y + 80.f);
    popupOkButton.setOutlineThickness(2.f);
    popupOkButton.setOutlineColor(sf::Color::White);

    popupOkText.setFont(font);
    popupOkText.setString("OK");
    popupOkText.setCharacterSize(24);
    popupOkText.setFillColor(sf::Color::White);
    popupOkText.setPosition(popupOkButton.getPosition().x + 30.f, popupOkButton.getPosition().y + 5.f);

    if (totalRounds < 10) {
        popupVisible = true;
    }
    totalRounds++;
    if (resultMessage == "YOU WIN") totalWins++;
    else totalLosses++;

    if (totalRounds >= 10) {
        InitFinalPopup(font, window);
    }
}

void DrawResultPopup(sf::RenderWindow& window) {
    if (popupVisible) {
        RectangleHover::applyHoverEffect(popupOkButton, window, true);
        window.draw(popupBackground);
        window.draw(popupText);
        window.draw(popupOkButton);
        window.draw(popupOkText);
    }
    if (finalPopupVisible) {
        RectangleHover::applyHoverEffect(finalPopupOkButton, window, true);
        window.draw(finalPopupBackground);
        window.draw(finalPopupText);
        window.draw(finalPopupStats);
        window.draw(finalPopupOkButton);
        window.draw(finalPopupOkText);
    }
}

void HandleResultPopupClick(const sf::Vector2f& mousePos) {
    if (finalPopupVisible) {
        AudioManager::playClick();
        if (finalPopupOkButton.getGlobalBounds().contains(mousePos)) {
            finalPopupVisible = false;
            totalRounds = totalWins = totalLosses = totalScorePlayer = totalScoreComputer = 0;
            allowInput = true; // разблокируем ввод
        }
        return;
    }

    if (popupVisible && popupOkButton.getGlobalBounds().contains(mousePos)) {
        AudioManager::playClick();
        popupVisible = false;
    }
}

void InitHelpMenu(const sf::Font& font, const sf::RenderWindow& window) {
    helpMenuBackground.setSize(sf::Vector2f(400.f, static_cast<float>(window.getSize().y)));
    helpMenuBackground.setFillColor(sf::Color(0, 0, 0, 150));
    helpMenuBackground.setPosition(0.f, 0.f);

    helpTitle.setFont(font);
    helpTitle.setString("Combinations");
    helpTitle.setCharacterSize(28);
    helpTitle.setFillColor(sf::Color::White);
    helpTitle.setPosition(20.f, 20.f);

    std::vector<std::string> combinations = {
        "Pair: Two same dice",
        "Three of a kind: Three same dice",
        "Straight: 1-2-3-4-5 or 2-3-4-5-6",
        "Full House: Pair + Three of a kind",
        "Four of a kind: Four same dice",
        "Five of a kind: All dice same",
        "Yahtzee Combo: Special roll"
    };

    float y = 70.f;
    for (const std::string& text : combinations) {
        sf::Text item;
        item.setFont(font);
        item.setString("- " + text);
        item.setCharacterSize(20);
        item.setFillColor(sf::Color::White);
        item.setPosition(20.f, y);
        y += 40.f;
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
        "- To win a round, the player must score more points than the computer.",
"- By clicking the left mouse button on a die, you can reroll it (up to 3 times in total).",
"- Pressing the R key rerolls all dice, but only once.",
"- In one game, you can reveal only 2 of the opponent's dice."
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

void UpdateRerollTexts(int totalRerolls, int allRerolls, const sf::Font& font, const sf::RenderWindow& window) {
    rerollInfo.setFont(font);
    rerollInfo.setCharacterSize(20);
    rerollInfo.setFillColor(sf::Color::Yellow);
    rerollInfo.setString("Remaining rerolls: " + std::to_string(totalRerolls));
    rerollInfo.setPosition(20.f, static_cast<float>(window.getSize().y) - 60.f);

    allrerollInfo.setFont(font);
    allrerollInfo.setCharacterSize(20);
    allrerollInfo.setFillColor(sf::Color::Cyan);
    allrerollInfo.setString("Full reroll available: " + std::to_string(allRerolls));
    allrerollInfo.setPosition(20.f, static_cast<float>(window.getSize().y) - 30.f);
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

    sf::Text titleScore = TextAnimator::createText("Score:", font, 90, sf::Color::White);
    sf::Text titleScoreOutline = TextAnimator::createText("Score:", font, 90, sf::Color::Black);

    titleScore.setPosition(window.getSize().x / 2.f +  100, window.getSize().y /1.4);
    titleScoreOutline.setPosition(titleScore.getPosition());

    SwayText2 swayScore(titleScore, titleScore.getPosition());
    SwayText2 swayScoreOutline(titleScoreOutline, titleScore.getPosition());

    sf::Text titleRules = TextAnimator::createText("rules", font, 60, sf::Color::White);
    sf::Text titleRulesOutline = TextAnimator::createText("rules", font, 60, sf::Color::Black);

    titleRules.setPosition(window.getSize().x / 10.f, window.getSize().y / 1.1);
    titleRulesOutline.setPosition(titleRules.getPosition());

    SwayText1 swayRules(titleRules, titleRules.getPosition());
    SwayText1 swayRulesOutline(titleRulesOutline, titleRules.getPosition());

    sf::Text ScoreComputer = TextAnimator::createText("Computer Score:", font, 90, sf::Color::White);
    sf::Text ScoreComputerOutline = TextAnimator::createText("Computer Score:", font, 90, sf::Color::Black);

    ScoreComputer.setPosition(window.getSize().x / 2.f + 100, window.getSize().y / 4.f);
    ScoreComputerOutline.setPosition(ScoreComputer.getPosition());

    SwayText1 swayComputer(ScoreComputer, ScoreComputer.getPosition());
    SwayText1 swayComputerOutline(ScoreComputerOutline, ScoreComputer.getPosition());

    sf::Text EndRound = TextAnimator::createText("END ROUND", font, 90, sf::Color::White);
    sf::Text EndRoundOutline = TextAnimator::createText("END ROUND", font, 90, sf::Color::Black);

    EndRound.setPosition(window.getSize().x / 5.f, window.getSize().y / 1.95);
    EndRoundOutline.setPosition(EndRound.getPosition());

    SwayText1 swayEndRound(EndRound, EndRound.getPosition());
    SwayText1 swayEndRoundOutline(EndRoundOutline, EndRound.getPosition());

    sf::Text totalRounds = TextAnimator::createText("ROUND", font, 70, sf::Color::White);
    sf::Text totalRoundsOutline = TextAnimator::createText("ROUND", font, 70, sf::Color::Black);

    totalRounds.setPosition(window.getSize().x / 11.f, window.getSize().y / 1.4);
    totalRoundsOutline.setPosition(totalRounds.getPosition());

    SwayText2 swaytotalRounds(totalRounds, totalRounds.getPosition());
    SwayText2 swaytotalRoundsOutline(totalRoundsOutline, totalRounds.getPosition());

    sf::Text resultText;
    sf::Text resultOutline;
    resultText.setFont(font);
    resultText.setCharacterSize(100);
    resultText.setPosition(window.getSize().x / 2.f  + 300, window.getSize().y / 2.f);

    resultOutline.setFillColor(sf::Color::Black);
    resultOutline.setPosition(resultText.getPosition().x + 2, resultText.getPosition().y + 2);

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

    sf::RectangleShape playerPanel;
    playerPanel.setSize(sf::Vector2f({400.f, 100.f}));
    playerPanel.setFillColor(sf::Color(30, 30, 30, 200));
    playerPanel.setPosition(window.getSize().x / 2.1, window.getSize().y /1.42);
    playerPanel.setOutlineThickness(2);
    playerPanel.setOutlineColor(sf::Color::White);

    sf::RectangleShape computerPanel;
    computerPanel.setSize(sf::Vector2f({700.f, 100.f}));
    computerPanel.setFillColor(sf::Color(30, 30, 30, 200));
    computerPanel.setPosition(window.getSize().x / 2.5, window.getSize().y / 4.2);
    computerPanel.setOutlineThickness(2);
    computerPanel.setOutlineColor(sf::Color::White);

    sf::RectangleShape endRoundPanel;
    endRoundPanel.setSize(sf::Vector2f({400.f, 100.f}));
    endRoundPanel.setFillColor(sf::Color(30, 30, 30, 200));
    endRoundPanel.setPosition(window.getSize().x / 10, window.getSize().y / 2);
    endRoundPanel.setOutlineThickness(2);
    endRoundPanel.setOutlineColor(sf::Color::White);

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
    int revealedEnemyDice = 2;
    std::vector<bool> enemyDiceRevealed(5, true);
    bool endRound = false;
    bool playerWon = false;
    bool roundEnded = false;

    while (window.isOpen()) {
            sf::Event event;
            int score = DicesBalatro::calculateDiceScore(diceSprites, diceTextures);
            int scorecomputer  = DicesBalatro::calculateDiceScore(diceComputer, diceTextures);
            for (size_t i=0; i < diceSprites.size(); ++i) {
                diceSprites[i].handelEvent(event, window, i);
            }
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    HandleResultPopupClick(mouse); // позволяет нажать OK в финальном окне
                }
                if (!allowInput) continue;

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
                    if (gameRules && !helpMenuBackground.getGlobalBounds().contains(mouse)) {
                        gameRules = false;
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
                    for (size_t i = 0; i < noComputer.size(); ++i) {
                        if (enemyDiceRevealed[i] && noComputer[i].getSprite()->getGlobalBounds().contains(mouse)) {
                            if (revealedEnemyDice > 0) {
                                enemyDiceRevealed[i] = false;
                                revealedEnemyDice--;
                                AudioManager::playClick();
                                break;
                            }
                        }
                    }
                    if (EndRound.getGlobalBounds().contains(mouse)) {
                        DicesBalatro::rerollDiceSet(diceSprites, diceTextures);
                        DicesBalatro::rerollDiceSet(diceComputer, diceTextures);
                        AudioManager::playClick();
                        endRound = true;
                        int playerScore = DicesBalatro::calculateDiceScore(diceSprites, diceTextures);
                        int computerScore = DicesBalatro::calculateDiceScore(diceComputer, diceTextures);
                        playerWon = (playerScore >= computerScore);
                        roundEnded = true;
                        InitResultPopup(playerWon ? "YOU WIN" : "YOU LOSE", font, window);
                        resultOutline = resultText;
                        totalRerolls = 3;
                        allReroles = 1;
                        revealedEnemyDice = 2;
                        for (size_t i = 0; i < noComputer.size(); ++i) {
                            enemyDiceRevealed[i] = true;
                        }
                        totalScorePlayer += score;
                        totalScoreComputer += scorecomputer;
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
                TextAnimator::applyHoverEffect(EndRound, EndRoundOutline, window);
            }

            if (!fadefinished) {
                fadefinished = true;
                FadeEffect::fadeIn(window, {&backgroundSprite, diceSprites[0].getSprite(),
                diceSprites[1].getSprite()}, 1);
            }

            UpdateRerollTexts(totalRerolls, allReroles, font, window);
            int lastDiceScore = score;
            std::cout << score << std::endl;
            titleScore.setString("Score: " + std::to_string(score));
            ScoreComputer.setString("Computer Score: " + std::to_string(scorecomputer));
            totalRounds.setString("ROUNDS: " + std::to_string(::totalRounds));
            totalRoundsOutline.setString("ROUNDS: " + std::to_string(::totalRounds));
            float swayTime = swayClock.getElapsedTime().asSeconds();
            window.clear();
            window.draw(backgroundSprite);
            window.draw(leftPanel);
            window.draw(downPanel);
            window.draw(topPanel);
            window.draw(playerPanel);
            window.draw(computerPanel);
            window.draw(endRoundPanel);
            swayMenu.update(swayTime);
            swayTab.update(swayTime);
            swayScore.update(swayTime);
            swayRules.update(swayTime);
            swayMenuOutline.update(swayTime);
            swayComputer.update(swayTime);
            swayComputerOutline.update(swayTime);
            swayRulesOutline.update(swayTime);
            swayScoreOutline.update(swayTime);
            swayTabOutline.update(swayTime);
            swayEndRoundOutline.update(swayTime);
            swayEndRound.update(swayTime);
            swaytotalRounds.update(swayTime);
            swaytotalRoundsOutline.update(swayTime);
            window.draw(rerollInfo);
            window.draw(allrerollInfo);
            TextAnimator::drawWithOutline(window, titleMenu, titleMenuOutline);
            TextAnimator::drawWithOutline(window, titleTab, titleTabOutline);
            TextAnimator::drawWithOutline(window, titleScore, titleScoreOutline);
            TextAnimator::drawWithOutline(window, titleRules, titleRulesOutline);
            TextAnimator::drawWithOutline(window, EndRound, EndRoundOutline);
            TextAnimator::drawWithOutline(window, totalRounds, totalRoundsOutline);
            DrawResultPopup(window);
            for (auto& dice : diceSprites) {
                dice.draw(window);
            }
            for (auto& dice : diceComputer) {
                dice.draw(window); // верхний ряд
            }
            for (size_t i = 0; i < noComputer.size(); ++i) {
                if (enemyDiceRevealed[i]) {
                    noComputer[i].draw(window);
                }
            }
            if (roundEnded) {
                window.draw(resultOutline);
                window.draw(resultText);
                TextAnimator::drawWithOutline(window, ScoreComputer, ScoreComputerOutline);
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