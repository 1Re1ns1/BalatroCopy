//
// Created by artem on 19.03.2025.
//

#include "TextInput.h"

std::string userInput = ""; // Инициализация переменной

void HandleTextInput(sf::Event event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) { // Фильтруем ASCII-символы
            if (event.text.unicode == 8) { // Backspace (удаление последнего символа)
                if (!userInput.empty()) {
                    userInput.pop_back();
                }
            } else if (userInput.length() < 100) { // Ограничение длины текста
                userInput += static_cast<char>(event.text.unicode);
            }
        }
    }
}