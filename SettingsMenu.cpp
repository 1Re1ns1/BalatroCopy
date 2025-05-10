#include "SettingsMenu.h"
#include <SFML/Graphics.hpp>
#include "AudioManager.h"
#include <iostream>
#include "MenuBalatro.h"
#include <cmath>
#include "VolumeSlider.h"
#include "TextAnimator.h"
#include <unordered_map>

extern sf::RenderWindow window;
extern bool isFullscreen;

void recreateWindow(bool fullscreen) {
    isFullscreen = fullscreen;
    window.close();

    sf::VideoMode mode = fullscreen ? sf::VideoMode::getDesktopMode() : sf::VideoMode(1280, 720);
    sf::Uint32 style = fullscreen ? sf::Style::Fullscreen : (sf::Style::Titlebar | sf::Style::Close);

    window.create(mode, "Gra Kosciana", style);
    window.setFramerateLimit(60);
}

std::unordered_map<sf::Sprite*, sf::Vector2f> originalSpriteScales;
std::unordered_map<sf::Sprite*, sf::Vector2f> originalSpritePositions;

void ApplyHoverEffectSprite(sf::Sprite& sprite, sf::RenderWindow& window) {
    if (Animation) {
        if (originalSpriteScales.find(&sprite) == originalSpriteScales.end()) {
            originalSpriteScales[&sprite] = sprite.getScale();
            originalSpritePositions[&sprite] = sprite.getPosition();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        if (sprite.getGlobalBounds().contains(worldPos)) {
            if (sprite.getScale() == originalSpriteScales[&sprite]) {
                sf::Vector2f newScale = originalSpriteScales[&sprite] * 1.1f;
                sprite.setScale(newScale);

                sf::FloatRect bounds = sprite.getGlobalBounds();
                sf::Vector2f center = {
                    originalSpritePositions[&sprite].x + bounds.width / 2,
                    originalSpritePositions[&sprite].y + bounds.height / 2
                };
                sprite.setPosition(center.x - bounds.width / 2, center.y - bounds.height / 2);
            }
        } else {
            if (sprite.getScale() != originalSpriteScales[&sprite]) {
                sprite.setScale(originalSpriteScales[&sprite]);
                sprite.setPosition(originalSpritePositions[&sprite]);
            }
        }
    }
}

sf::RectangleShape createRoundedOverlay(const sf::RenderWindow& window) {
    sf::Vector2f windowSize(window.getSize());
    sf::RectangleShape overlay;

    sf::Vector2f size(windowSize.x * 0.8f, windowSize.y * 0.8f);
    overlay.setSize(size);
    overlay.setOrigin(size.x / 2, size.y / 2);
    overlay.setPosition(windowSize.x / 2, windowSize.y / 2);
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    overlay.setOutlineThickness(5);
    overlay.setOutlineColor(sf::Color::Black);

    return overlay;
}

void SettingsMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Fonts/m6x11plus.ttf")) return;

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Pictures/backgroundMenu.png")) return;

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    float volume = AudioManager::getMasterVolume();

    sf::Texture barBackgroundTexture;
    if (!barBackgroundTexture.loadFromFile("Pictures/f05b77c373169abdfda994fc35ef31af.png")) return;

    sf::Texture barFillTexture;
    if (!barFillTexture.loadFromFile("Pictures/279fba3df9b1b2b75bc63755dd49ac8a.png")) return;

    sf::Texture buttonok;
    if (!buttonok.loadFromFile("Pictures/buttongrean.png")) return;
    sf::Sprite buttonokSprite(buttonok);
    buttonokSprite.setScale(0.3f, 0.3f);

    sf::Texture buttonno;
    if (!buttonno.loadFromFile("Pictures/buttonred.png")) return;
    sf::Sprite buttonnoSprite(buttonno);
    buttonnoSprite.setScale(0.3f, 0.3f);

    VolumeSlider masterSlider(barBackgroundTexture, barFillTexture, font,
                              {window.getSize().x / 2.f - 200, window.getSize().y / 4.f}, 2.f);
    masterSlider.setVolume(volume);

    VolumeSlider musicSlider(barBackgroundTexture, barFillTexture, font,
                             {window.getSize().x / 2.f - 200, window.getSize().y / 6.f}, 2.f);
    musicSlider.setVolume(AudioManager::getMusicVolume());

    sf::Text title2 = TextAnimator::createText("Exit", font, 100, sf::Color::White);
    sf::Text outlinetitle2 = TextAnimator::createText("Exit", font, 100, sf::Color::Black);

    sf::Text musicvolume = TextAnimator::createText("Music Volume", font, 80, sf::Color::White);
    sf::Text mastervolume = TextAnimator::createText("Master Volume", font, 80, sf::Color::White);
    sf::Text animetiontext = TextAnimator::createText("Animation", font, 80, sf::Color::White);
    sf::Text fullscreenText = TextAnimator::createText("Fullscreen", font, 80, sf::Color::White);
    sf::Text options = TextAnimator::createText("Options", font, 100, sf::Color::White);

    musicvolume.setPosition(window.getSize().x / 6.f + 100.f, window.getSize().y / 7.f);
    mastervolume.setPosition(window.getSize().x / 6.f + 100.f, window.getSize().y / 7.f + 120);
    animetiontext.setPosition(window.getSize().x / 6.f + 100.f, window.getSize().y / 7.f + 240);
    fullscreenText.setPosition(window.getSize().x / 6.f + 100.f, window.getSize().y / 7.f + 360);
    options.setPosition(window.getSize().x / 2, 30);

    buttonokSprite.setPosition(window.getSize().x / 1.5f, window.getSize().y / 3.f);
    buttonnoSprite.setPosition(window.getSize().x / 1.5f, window.getSize().y / 3.f);

    sf::RectangleShape roundedBox = createRoundedOverlay(window);
    sf::Clock swayClock;
    float baseY = window.getSize().y / 2;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            TextAnimator::applyHoverEffect(title2, outlinetitle2, window);
            ApplyHoverEffectSprite(buttonokSprite, window);
            ApplyHoverEffectSprite(buttonnoSprite, window);

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                AudioManager::playClick();
                return;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (masterSlider.isHovering(mousePos)) masterSlider.setDragging(true);
                if (musicSlider.isHovering(mousePos)) musicSlider.setDragging(true);
                if (title2.getGlobalBounds().contains(mousePos)) {
                    AudioManager::playClick();
                    return;
                }

                if (Animation) {
                    if (buttonokSprite.getGlobalBounds().contains(mousePos)) {
                        Animation = false;
                        AudioManager::playClick();
                    }
                } else {
                    if (buttonnoSprite.getGlobalBounds().contains(mousePos)) {
                        Animation = true;
                        AudioManager::playClick();
                    }
                }

                if (fullscreenText.getGlobalBounds().contains(mousePos)) {
                    isFullscreen = !isFullscreen;
                    AudioManager::saveConfig();
                    recreateWindow(isFullscreen);
                    SettingsMenu(window); // Перезапускаем меню уже с новым окном
                    return;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                masterSlider.setDragging(false);
                musicSlider.setDragging(false);
            }

            if (event.type == sf::Event::MouseMoved) {
                if (masterSlider.isDragging()) {
                    masterSlider.updateFromMouse(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                    AudioManager::setMasterVolume(masterSlider.getVolume());
                    AudioManager::saveConfig();
                }
                if (musicSlider.isDragging()) {
                    musicSlider.updateFromMouse(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                    AudioManager::setMusicVolume(musicSlider.getVolume());
                    AudioManager::saveConfig();
                }
            }
        }

        float sway = std::sin(swayClock.getElapsedTime().asSeconds() * 2.f) * 5.f;
        title2.setPosition(window.getSize().x / 2.f + sway, baseY + 500.f);
        outlinetitle2.setPosition(window.getSize().x / 2.f + sway, baseY + 500.f);

        window.clear(sf::Color(30, 30, 30));
        window.draw(backgroundSprite);
        window.draw(roundedBox);
        TextAnimator::drawWithOutline(window, title2, outlinetitle2);
        window.draw(musicvolume);
        window.draw(mastervolume);
        window.draw(animetiontext);
        window.draw(fullscreenText);
        window.draw(options);
        masterSlider.draw(window);
        musicSlider.draw(window);

        if (Animation)
            window.draw(buttonokSprite);
        else
            window.draw(buttonnoSprite);

        window.display();
    }
}
