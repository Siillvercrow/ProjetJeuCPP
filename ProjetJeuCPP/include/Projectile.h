#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(const sf::Vector2f& startPosition, const sf::Texture& texture);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen() const;

    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    float speed;
};

#endif // PROJECTILE_H
