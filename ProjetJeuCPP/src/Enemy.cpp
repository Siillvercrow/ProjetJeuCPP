#include "Enemy.h"
#include <GameManager.h>

Enemy::Enemy(const sf::Vector2f& startPosition, const sf::Texture& texture)
    : speed(150.0f),downWardSpeed(230.0f), direction(1), isMovingDown(false), moveDownDuration(1.0f){
    sprite.setTexture(texture);
    sprite.setPosition(startPosition);
}

void Enemy::update(float deltaTime, const sf::Vector2u& windowSize) {
    // Si l'ennemi est en train de descendre
    if (isMovingDown) {
        // Descendre l'ennemi
        sprite.move(0, downWardSpeed * deltaTime);

        // Si le temps de descente est �coul�
        if (moveDownTimer.getElapsedTime().asSeconds() >= moveDownDuration) {
            isMovingDown = false; // Arr�ter la descente
            direction *= -1; // Changer la direction horizontale
            moveDownTimer.restart(); // R�initialiser le timer (pour une utilisation future)
        }
    }
    else {
        // D�placer l'ennemi horizontalement
        sprite.move(speed * deltaTime * direction, 0);

        // V�rifier la collision avec les bords de l'�cran
        if (sprite.getPosition().x + sprite.getGlobalBounds().width >= windowSize.x+1 || sprite.getPosition().x <= 1) {
            isMovingDown = true; // Commencer la descente
            moveDownTimer.restart(); // D�marrer le timer de descente
        }
    }
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Enemy::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void Enemy::destroy() {
    active = false;
    
}

bool Enemy::isActive() const {
    return active;
}

//get position
sf::Vector2f Enemy::getPosition() const {
	return sprite.getPosition();
}

