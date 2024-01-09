#include "GameManager.h"
#include <iostream>

GameManager::GameManager() : window(sf::VideoMode::getDesktopMode(), "Space Invaders", sf::Style::Fullscreen) {
    window.setFramerateLimit(60);
    // Chargement des textures et gestion des erreurs appropriées
    if (!playerTexture.loadFromFile("res/img/Vaisseau.png") ||
        !projectileTexture.loadFromFile("res/img/Projectiles/TireDroit.png") ||
        !enemyTexture.loadFromFile("res/img/Ennemies/EnnemieNv1.png")) {
        std::cerr << "Erreur de chargement des textures" << std::endl;
        throw std::runtime_error("Failed to load textures");
    }

    spawnPlayer(); // Initialisation du joueur
    spawnEnemies(); // Initialisation des ennemis
}

void GameManager::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
        }

        float deltaTime = clock.restart().asSeconds();
        update(deltaTime); // Mise à jour du jeu
        draw(); // Dessin du jeu
    }
}

void GameManager::spawnPlayer() {
    player = Player(window.getSize(), playerTexture, projectileTexture);

}

void GameManager::update(float deltaTime) {
    player.handleInput(); // Gestion des entrées du joueur
    player.update(deltaTime); // Mise à jour du joueur

    for (auto& enemy : enemies) {
        enemy->update(deltaTime, window.getSize()); // Mise à jour des ennemis
    }

    handleCollisions(); // Gestion des collisions
}

void GameManager::draw() {
    window.clear();

    player.draw(window); // Dessiner le joueur
   
    for (auto& enemy : enemies) {
        enemy->draw(window); // Dessiner les ennemis
    }

    window.display();
}

void GameManager::handleCollisions() {
    auto& projectiles = player.getProjectiles();

    // Parcourir tous les projectiles
    for (auto projIt = projectiles.begin(); projIt != projectiles.end();) {
        bool projectileErased = false;

        // Parcourir tous les ennemis
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end() && !projectileErased;) {
            if (projIt->getBounds().intersects((*enemyIt)->getBounds())) {
                // Collision détectée, supprimer l'ennemi et le projectile
                enemyIt = enemies.erase(enemyIt);
                projIt = projectiles.erase(projIt);
                projectileErased = true;
            }
            else {
                ++enemyIt;
            }
        }

        if (!projectileErased) {
            ++projIt;
        }
    }
}

void GameManager::spawnEnemies() {
    
    const int numEnemiesX = 5; // Nombre d'ennemis horizontalement
    const int numEnemiesY = 3; // Nombre d'ennemis verticalement
    const float spacingX = 300.0f; // Espacement horizontal entre les ennemis
    const float spacingY = 80.0f;  // Espacement vertical entre les ennemis
    sf::Vector2f startPosition(100, 50); // Position de départ pour le premier ennemi

    for (int y = 0; y < numEnemiesY; ++y) {
        for (int x = 0; x < numEnemiesX; ++x) {
            sf::Vector2f position = startPosition + sf::Vector2f(x * spacingX, y * spacingY);
            Enemy* enemy = new Enemy(position, enemyTexture);
            enemies.emplace_back(enemy);
        }
    }
}


