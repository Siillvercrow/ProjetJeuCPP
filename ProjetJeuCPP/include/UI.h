#pragma once
#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>

class UI {
public:
    UI();
    void setScore(int score);
    void draw(sf::RenderWindow& window);
    void displayWinMessage(sf::RenderWindow& window);
    void initialize(sf::Vector2u windowSize);
    void displayLoseMessage(sf::RenderWindow& window);


private:
    sf::Text winMessage;
    sf::Text loseMessage;
    sf::Font font;
    sf::Text scoreText;
    int currentScore;
};

#endif // UI_H
