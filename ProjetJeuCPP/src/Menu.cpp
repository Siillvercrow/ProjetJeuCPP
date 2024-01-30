#include "Menu.h"

Menu::Menu(sf::Vector2u windowSize) {
    if (!font.loadFromFile("res/space_invaders.ttf")) {
        // Gérer l'erreur de chargement de la police
    }

    title.setFont(font);
    title.setString("Space Invader");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::White);
    title.setPosition(windowSize.x / 2 - title.getLocalBounds().width / 2, 100);

    start.setFont(font);
    start.setString("Lancer");
    start.setCharacterSize(30);
    start.setFillColor(sf::Color::White);
    start.setPosition(windowSize.x / 2 - start.getLocalBounds().width / 2, 500);

    exit.setFont(font);
    exit.setString("Quitter");
    exit.setCharacterSize(30);
    exit.setFillColor(sf::Color::White);
    exit.setPosition(windowSize.x / 2 - exit.getLocalBounds().width / 2, 600);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(start);
    window.draw(exit);
}

bool Menu::isStartClicked(const sf::Vector2i& mousePos) const {
    return start.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool Menu::isExitClicked(const sf::Vector2i& mousePos) const {
    return exit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Menu::handleMouseHover(const sf::Vector2i& mousePos) {
    if (start.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        start.setFillColor(sf::Color::Green); // Change la couleur en vert
    }
    else {
        start.setFillColor(sf::Color::White); // Retour à la couleur normale
    }

    if (exit.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        exit.setFillColor(sf::Color::Red); // Change la couleur en rouge
    }
    else {
        exit.setFillColor(sf::Color::White); // Retour à la couleur normale
    }
}