#include "UI.h"
#include <iostream>
#include <string>


UI::UI() : currentScore(0) {
    // Charger la police depuis un fichier
    if (!font.loadFromFile("res/space_invaders.ttf")) {
        std::cerr << "Erreur de chargement de la police" << std::endl;
    }

    // Configurer le texte du score
    scoreText.setFont(font);
    scoreText.setCharacterSize(24); // Taille de la police
    scoreText.setFillColor(sf::Color::White); // Couleur du texte
    scoreText.setPosition(10, 10); // Position en haut à gauche
    setScore(0); // Initialiser le score à 0

    
}

// ... les autres parties de UI.cpp restent inchangées

void UI::initialize(sf::Vector2u windowSize) {
    // Configurer le message de victoire
    winMessage.setFont(font);
    winMessage.setCharacterSize(30); // Taille de la police
    winMessage.setFillColor(sf::Color::Green); // Couleur du texte
    winMessage.setString("Bravo ! Vous avez gagne !");
    sf::FloatRect textRect = winMessage.getLocalBounds();
    winMessage.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    winMessage.setPosition(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 2.0f);

    // Configurer le message de défaite
    loseMessage.setFont(font);
    loseMessage.setCharacterSize(30);
    loseMessage.setFillColor(sf::Color::Red);
    loseMessage.setString("Desole ! Vous avez perdu !");
    sf::FloatRect textRectL = loseMessage.getLocalBounds();
    loseMessage.setOrigin(textRectL.width / 2.0f, textRectL.height / 2.0f);
    loseMessage.setPosition(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 2.0f);
}

void UI::displayLoseMessage(sf::RenderWindow& window) {
    window.draw(loseMessage);
}


void UI::setScore(int score) {
    currentScore = score;
    scoreText.setString("Score: " + std::to_string(currentScore));
}

void UI::draw(sf::RenderWindow& window) {
    window.draw(scoreText);
}


void UI::displayWinMessage(sf::RenderWindow& window) {
    window.draw(winMessage);
}