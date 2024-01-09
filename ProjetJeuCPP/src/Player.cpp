#include "Player.h"
#include <iostream>

Player::Player() : speed(15.0f) {
	// Ne rien faire
}

Player::Player(const sf::Vector2u& windowSize, const sf::Texture& playerTexture, const sf::Texture& projTexture)
    : speed(15.0f), projectileTexture(projTexture) {
    sprite.setTexture(playerTexture);
    sprite.setPosition(windowSize.x / 2 - sprite.getGlobalBounds().width / 2,
        windowSize.y - sprite.getGlobalBounds().height);
    windowSizeX = windowSize.x;
}

void Player::handleInput() {
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) &&
        sprite.getPosition().x > 0) {
        sprite.move(-speed, 0);
    }
    // Déplacement vers la droite
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
        sprite.getPosition().x + sprite.getGlobalBounds().width < windowSizeX) {
        sprite.move(speed, 0);
    }
}

void Player::update(float deltaTime) {
    handleInput(); // Ajout de la gestion des entrées ici pour une meilleure encapsulation

    if (shootTimer.getElapsedTime().asSeconds() > 1.0f) {
        // Créer le projectile à la base du vaisseau, centré sur sa largeur.
        sf::Vector2f startPosition(
            sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - projectileTexture.getSize().x / 2,
            sprite.getPosition().y - projectileTexture.getSize().y // Ajustez cette ligne pour changer la position de départ en y.
        );
        projectiles.emplace_back(startPosition, projectileTexture);
        shootTimer.restart();
    }

    // Mettre à jour les projectiles
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        it->update(deltaTime);
        if (it->isOffScreen()) {
            it = projectiles.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    for (auto& projectile : projectiles) {
        projectile.draw(window);
    }
}

std::vector<Projectile>& Player::getProjectiles() {
    return projectiles;
}
