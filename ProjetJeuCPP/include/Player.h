#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"
#include <Enemy.h>

class Player {
public:
    Player();
    Player(const sf::Vector2u& windowSize, const sf::Texture& playerTexture, const sf::Vector2f& projectileSize, const sf::Color& projectileColor);
    void handleInput();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    std::vector<Projectile>& getProjectiles();
    unsigned int windowSizeX;
    sf::FloatRect getGlobalBounds() const;
    void destroy();
    bool isActive() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f projectileSize;
    sf::Color projectileColor;
    std::vector<Projectile> projectiles;
    sf::Texture projectileTexture;
    sf::Clock shootTimer;
    float speed;
    bool active;


};

#endif // PLAYER_H
