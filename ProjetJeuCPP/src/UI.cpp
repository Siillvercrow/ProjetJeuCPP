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

    exitGame.setFont(font);
    exitGame.setString("Quitter");
    exitGame.setCharacterSize(30);
    exitGame.setFillColor(sf::Color::White);
    exitGame.setPosition(windowSize.x / 2 - exitGame.getLocalBounds().width / 2, windowSize.y / 2 + 200);
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

void UI::displayExitMessage(sf::RenderWindow& window) {
    window.draw(exitGame);
}

bool UI::isExitClicked(const sf::Vector2i& mousePos) const {
    return exitGame.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void UI::handleMouseHover(const sf::Vector2i& mousePos) {
    // Gérer le survol pour le bouton "Quitter"
    if (exitGame.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        exitGame.setFillColor(sf::Color::Red); // Change la couleur en rouge lors du survol
    }
    else {
        exitGame.setFillColor(sf::Color::White); // Retour à la couleur blanche par défaut
    }
}