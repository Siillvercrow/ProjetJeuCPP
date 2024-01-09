#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Player.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>

class GameManager {
public:
    GameManager();  // Le constructeur n'a pas besoin de paramètres maintenant
    void run();  // Cette méthode lance le jeu

private:
    sf::RenderWindow window;
    Player player;
    std::vector<Enemy*> enemies;
    sf::Texture playerTexture, projectileTexture, enemyTexture;

    void update(float deltaTime);
    void draw();
    void handleCollisions();
    void spawnPlayer();
    void spawnEnemies();
};

#endif // GAMEMANAGER_H
