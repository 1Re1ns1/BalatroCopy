
#pragma once
#include <SFML/Graphics.hpp>
class VolumeSlider {
public:
    VolumeSlider(const sf::Texture& backgroundTex, const sf::Texture& fillTex, const sf::Font& font, sf::Vector2f position, float scale = 3.0f);

    void setVolume(float volume);       // Set volume (0 - 100)
    float getVolume() const;            // Get current volume
    void updateFromMouse(const sf::Vector2f& mousePos); // Update slider on drag
    void draw(sf::RenderWindow& window);               // Draw everything
    void setDragging(bool drag);        // Toggle dragging
    bool isDragging() const;
    bool isHovering(const sf::Vector2f& mousePos) const;


private:
    float volume;
    bool dragging;
    float scale;

    sf::Sprite backgroundSprite;
    sf::Sprite fillSprite;
    sf::Text volumeText;

    const sf::Texture& fillTexture;
};
