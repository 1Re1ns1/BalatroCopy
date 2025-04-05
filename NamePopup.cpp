
#include "NamePopup.h"
#include "AudioManager.h"
#include "GameMenu.h"
#include "RectangleHover.h"
#include "FadeEffect.h"

NamePopup::NamePopup() : visible(false) {}

void NamePopup::init(sf::Font& font, sf::Vector2u windowSize) {
    sf::Vector2f center(windowSize.x / 2.f, windowSize.y / 2.f);

    background.setSize({400, 200});
    background.setFillColor(sf::Color(50, 50, 50, 220));
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::White);
    background.setOrigin(background.getSize() / 2.f);
    background.setPosition(center);

    promptText.setFont(font);
    promptText.setString("Write your name:");
    promptText.setCharacterSize(20);
    promptText.setFillColor(sf::Color::White);
    promptText.setPosition(center.x - 180, center.y - 70);

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Cyan);
    inputText.setPosition(center.x - 180, center.y - 20);

    inputBox.setSize({300, 40});
    inputBox.setFillColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setPosition(center.x - 180, center.y - 25);

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
    backText.setPosition(backButton.getPosition().x + 10, backButton.getPosition().y + 5);
}

void NamePopup::handleEvent(const sf::Event& event, sf::RenderWindow& window, bool& showNamePopup, std::string& playerName, const std::vector<sf::Drawable*>& drawables) {
    if (!visible) return;

    RectangleHover::applyHoverEffect(okButton, window, true);
    RectangleHover::applyHoverEffect(backButton, window, true);

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && !inputString.empty()) {
            inputString.pop_back();
        } else if (event.text.unicode >= 32 && event.text.unicode < 128) {
            inputString += static_cast<char>(event.text.unicode);
        }
        inputText.setString(inputString);
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
        if (okButton.getGlobalBounds().contains(mouse)) {
            AudioManager::playClick();
            playerName = inputString;
            showNamePopup = false;
            visible = false;

            FadeEffect::fadeOut(window, drawables);  // Плавный fade out
            GameMenu(window); // Переход
        }
        if (backButton.getGlobalBounds().contains(mouse)) {
            AudioManager::playClick();
            showNamePopup = false;
            visible = false;
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            AudioManager::playClick();
            playerName = inputString;
            showNamePopup = false;
            visible = false;

            FadeEffect::fadeOut(window, drawables);  // Плавный fade out
            GameMenu(window);
        } else if (event.key.code == sf::Keyboard::Escape) {
            AudioManager::playClick();
            showNamePopup = false;
            visible = false;
        }
    }
}




void NamePopup::draw(sf::RenderWindow& window) {
    if (!visible) return;

    window.draw(background);
    window.draw(promptText);
    window.draw(inputBox);
    window.draw(inputText);
    window.draw(okButton);
    window.draw(okText);
    window.draw(backButton);
    window.draw(backText);
}

void NamePopup::show() {
    visible = true;
}

void NamePopup::hide() {
    visible = false;
}

bool NamePopup::isVisible() const {
    return visible;
}
