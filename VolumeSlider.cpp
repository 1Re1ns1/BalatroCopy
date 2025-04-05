
#include "VolumeSlider.h"
#include <sstream>
#include <iomanip>
VolumeSlider::VolumeSlider(const sf::Texture& backgroundTex, const sf::Texture& fillTex, const sf::Font& font, sf::Vector2f position, float scale)
    : volume(100.f), dragging(false), scale(scale), fillTexture(fillTex)
{
    backgroundSprite.setTexture(backgroundTex);
    backgroundSprite.setScale(scale, scale);
    backgroundSprite.setPosition(position);

    fillSprite.setTexture(fillTex);
    fillSprite.setScale(scale, scale);
    fillSprite.setPosition(position);

    volumeText.setFont(font);
    volumeText.setCharacterSize(30);
    volumeText.setFillColor(sf::Color::White);
    volumeText.setStyle(sf::Text::Bold);
    volumeText.setPosition(position.x + backgroundSprite.getGlobalBounds().width - 170, position.y+30);
}

void VolumeSlider::setVolume(float vol) {
    volume = std::clamp(vol, 0.f, 100.f);
}

float VolumeSlider::getVolume() const {
    return volume;
}

void VolumeSlider::setDragging(bool drag) {
    dragging = drag;
}

void VolumeSlider::updateFromMouse(const sf::Vector2f& mousePos) {
    float x = backgroundSprite.getPosition().x;
    float width = backgroundSprite.getGlobalBounds().width;
    volume = std::clamp(((mousePos.x - x) / width) * 100.f, 0.f, 100.f);
}

void VolumeSlider::draw(sf::RenderWindow& window) {
    int fillWidth = static_cast<int>((volume / 100.f) * fillTexture.getSize().x);
    sf::IntRect fillRect(0, 0, fillWidth, fillTexture.getSize().y);
    fillSprite.setTextureRect(fillRect);

    fillSprite.setScale(scale, scale);

    std::ostringstream ss;
    ss << static_cast<int>(volume);
    volumeText.setString(ss.str());

    window.draw(backgroundSprite);
    window.draw(fillSprite);
    window.draw(volumeText);
}

bool VolumeSlider::isHovering(const sf::Vector2f& mousePos) const {
    return backgroundSprite.getGlobalBounds().contains(mousePos);
}

bool VolumeSlider::isDragging() const {
    return dragging;
}