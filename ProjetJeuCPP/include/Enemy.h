#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2f& startPosition, const sf::Texture& texture);
    void update(float deltaTime, const sf::Vector2u& windowSize);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    float speed;
    float downWardSpeed;
    int direction;
    bool isMovingDown; 
    sf::Clock moveDownTimer; 
    const float moveDownDuration; 
};

#endif // ENEMY_H
