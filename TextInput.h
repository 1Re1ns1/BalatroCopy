//
// Created by artem on 19.03.2025.
//

#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <SFML/Graphics.hpp>
#include <string>

extern std::string userInput; // Глобальная переменная для хранения введённого текста

void HandleTextInput(sf::Event event);



#endif //TEXTINPUT_H
