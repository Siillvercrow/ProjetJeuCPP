#include "GameManager.h"
#include <iostream>

GameManager::GameManager() : window(sf::VideoMode::getDesktopMode(), "Space Invaders", sf::Style::Fullscreen), score(0), gameWon(false), gameLost(false), isMenuActive(true), menu(window.getSize()) {
    
    // Chargement des textures et gestion des erreurs appropriées
    if (!playerTexture.loadFromFile("res/img/Vaisseau.png") ||
        !projectileTexture.loadFromFile("res/img/Projectiles/TireDroit.png") ||
        !enemyTexture.loadFromFile("res/img/Ennemies/EnnemieNv1.png")) {
        std::cerr << "Erreur de chargement des textures" << std::endl;
        throw std::runtime_error("Failed to load textures");
    }
    gameUI.initialize(window.getSize());
    gameUI.setScore(score);
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
            if (event.type == sf::Event::MouseButtonPressed) {
                if (menu.isStartClicked(sf::Mouse::getPosition(window))) {
                    isMenuActive = false; // Commencer le jeu
                }

                if (menu.isExitClicked(sf::Mouse::getPosition(window))) {
                    window.close(); // Fermer le jeu
                }
            }
            if (gameWon || gameLost) {
                gameUI.handleMouseHover(sf::Mouse::getPosition(window)); // Gérer le survol
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (gameUI.isExitClicked(sf::Mouse::getPosition(window))) {
                        window.close(); // Fermer le jeu
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        
        window.clear();
        if (isMenuActive) {
            menu.draw(window);
            menu.handleMouseHover(sf::Mouse::getPosition(window));
        }
        else {
            
            update(deltaTime); // Mise à jour du jeu
            draw(); // Dessin du jeu
        }



        window.display();

      
    }
}

void GameManager::spawnPlayer() {
    sf::Vector2f projectileSize(5.0f, 30.0f); 
    sf::Color projectileColor = sf::Color::White;
    player = Player(window.getSize(), playerTexture, projectileSize, projectileColor);

}

bool GameManager::checkWinCondition() const {
    return enemies.empty();
}

void GameManager::update(float deltaTime) {

    if (!gameWon && !gameLost && !isMenuActive) {
        player.handleInput(); // Gestion des entrées du joueur
        player.update(deltaTime); // Mise à jour du joueur

        for (auto& enemy : enemies) {
            if (enemy->isActive()) {
                enemy->update(deltaTime, window.getSize());
                if (enemy->getGlobalBounds().intersects(player.getGlobalBounds()) ||
                    enemy->getPosition().y + enemy->getGlobalBounds().height >= window.getSize().y) {
                    std::cout << "Game lost condition met." << std::endl; // Pour le débogage
                    player.destroy(); // Détruire le joueur
                    for (auto& e : enemies) { e->destroy(); } // Détruire tous les ennemis
                    //gameWon = true; // Utiliser gameWon pour indiquer la fin du jeu
                    gameLost = true; // Indiquer que le jeu est perdu
                    break;
                }
            }
        }

        handleCollisions();

        if (checkWinCondition()) {
            gameWon = true;
            player.destroy();
        }
    }

    

    handleCollisions(); // Gestion des collisions
}

void GameManager::draw() {
    window.clear();

    
    if (gameWon) {
        gameUI.displayWinMessage(window);
        gameUI.displayExitMessage(window);
    }
    else if (gameLost) {
        
        gameUI.displayLoseMessage(window);
        gameUI.displayExitMessage(window);
    }
   
    else {
        if (player.isActive()) {
            player.draw(window);
        }
        for (auto& enemy : enemies) {
            if (enemy->isActive()) {
                enemy->draw(window);
            }
        }
    }

    gameUI.draw(window);
    window.display();
}

void GameManager::handleCollisions() {
    //if the game is won or lose, don't check for collisions
    if (gameWon || gameLost) {
		return;
	}
    auto& projectiles = player.getProjectiles();

    // Parcourir tous les projectiles
    for (auto projIt = projectiles.begin(); projIt != projectiles.end();) {
        bool projectileErased = false;

        // Parcourir tous les ennemis
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end() && !projectileErased;) {
            if (projIt->getGlobalBounds().intersects((*enemyIt)->getGlobalBounds())) {
                // Collision détectée, supprimer l'ennemi et le projectile
                enemyIt = enemies.erase(enemyIt);
                projIt = projectiles.erase(projIt);
                projectileErased = true;
                score++;
                std::cout << score << std::endl;
                gameUI.setScore(score);
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


