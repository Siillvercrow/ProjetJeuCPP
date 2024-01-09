#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"
#include <Enemy.h>

class Player {
public:
    Player();
    Player(const sf::Vector2u& windowSize, const sf::Texture& playerTexture, const sf::Texture& projectileTexture);
    void handleInput();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    std::vector<Projectile>& getProjectiles();
    unsigned int windowSizeX;
private:
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<Projectile> projectiles;
    sf::Texture projectileTexture;
    sf::Clock shootTimer;
    float speed;
    
};

#endif // PLAYER_H
