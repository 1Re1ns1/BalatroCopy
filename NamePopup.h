
#ifndef NAMEPOPUP_H
#define NAMEPOPUP_H

#include <SFML/Graphics.hpp>
#include <string>

class NamePopup {
public:
    NamePopup();

    void init(sf::Font& font, sf::Vector2u windowSize);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, bool& showNamePopup, std::string& playerName, const std::vector<sf::Drawable*>& drawables);
    void draw(sf::RenderWindow& window);

    void show();
    void hide();
    bool isVisible() const;

    bool visible = false;

    sf::RectangleShape background;
    sf::Text promptText;
    sf::Text inputText;
    sf::RectangleShape inputBox;
    sf::RectangleShape okButton;
    sf::Text okText;
    sf::RectangleShape backButton;
    sf::Text backText;
    std::string inputString;
};

#endif // NAMEPOPUP_H
