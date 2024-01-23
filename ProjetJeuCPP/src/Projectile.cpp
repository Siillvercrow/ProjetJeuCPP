#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& size, const sf::Color& color)
    : speed(500.0f) { 
    rectangle.setSize(size);
    rectangle.setFillColor(color);
    rectangle.setPosition(startPosition);
}

void Projectile::update(float deltaTime) {
    
    rectangle.move(0, -speed * deltaTime);
}

void Projectile::draw(sf::RenderWindow& window) const {
    window.draw(rectangle);
}

bool Projectile::isOffScreen() const {
    return rectangle.getPosition().y + rectangle.getGlobalBounds().height < 0;
}

sf::FloatRect Projectile::getGlobalBounds() const {
    return rectangle.getGlobalBounds();
}
