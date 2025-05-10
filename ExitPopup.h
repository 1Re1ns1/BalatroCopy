//
// Created by artem on 03.04.2025.
//

#ifndef EXITPOPUP_H
#define EXITPOPUP_H
#include <SFML/Graphics.hpp>


class ExitPopup {
public:
    ExitPopup();
    void init(sf::Font& font, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window,
                 bool& shouldExit, bool& showBackPopup,
                 const std::vector<sf::Drawable*>& drawablesToFade);
    bool isVisible() const;
    void show();
    void hide();

    sf::RectangleShape background;
    sf::RectangleShape okButton;
    sf::Text okText;
    sf::RectangleShape backButton;
    sf::Text backText;
    sf::Text promptText;
    bool visible;
};



#endif //EXITPOPUP_H
