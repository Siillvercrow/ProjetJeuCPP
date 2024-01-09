#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& startPosition, const sf::Texture& texture)
    : speed(500.0f) {  
    sprite.setTexture(texture);
    sprite.setPosition(startPosition);
}

void Projectile::update(float deltaTime) {
    
    sprite.move(0, -speed * deltaTime);
}

void Projectile::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Projectile::isOffScreen() const {
    return sprite.getPosition().y + sprite.getGlobalBounds().height < 0;
}

sf::FloatRect Projectile::getBounds() const {
    return sprite.getGlobalBounds();
}
