#include "Enemy.h"
#include <GameManager.h>

Enemy::Enemy(const sf::Vector2f& startPosition, const sf::Texture& texture)
    : speed(100.0f),downWardSpeed(80.0f), direction(1), isMovingDown(false), moveDownDuration(1.0f){
    sprite.setTexture(texture);
    sprite.setPosition(startPosition);
}

void Enemy::update(float deltaTime, const sf::Vector2u& windowSize) {
    // Si l'ennemi est en train de descendre
    if (isMovingDown) {
        // Descendre l'ennemi
        sprite.move(0, downWardSpeed * deltaTime);

        // Si le temps de descente est écoulé
        if (moveDownTimer.getElapsedTime().asSeconds() >= moveDownDuration) {
            isMovingDown = false; // Arrêter la descente
            direction *= -1; // Changer la direction horizontale
            moveDownTimer.restart(); // Réinitialiser le timer (pour une utilisation future)
        }
    }
    else {
        // Déplacer l'ennemi horizontalement
        sprite.move(speed * deltaTime * direction, 0);

        // Vérifier la collision avec les bords de l'écran
        if (sprite.getPosition().x + sprite.getGlobalBounds().width >= windowSize.x || sprite.getPosition().x <= 0) {
            isMovingDown = true; // Commencer la descente
            moveDownTimer.restart(); // Démarrer le timer de descente
        }
    }
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}
