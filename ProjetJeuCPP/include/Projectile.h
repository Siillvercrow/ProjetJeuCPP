#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

//

class Projectile {
public:
    Projectile(const sf::Vector2f& startPosition, const sf::Vector2f& size, const sf::Color& color);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen() const;

    sf::FloatRect getGlobalBounds() const;

private:
    sf::RectangleShape rectangle;
    float speed;
};

#endif // PROJECTILE_H
