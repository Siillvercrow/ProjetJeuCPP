#include <SFML/Graphics.hpp>
#include <iostream>
#include <GameManager.h>

int main() {

    try {
        GameManager gameManager;
        gameManager.run();  // Tout est géré dans cette méthode
    }
    catch (const std::exception& e) {
        std::cerr << "Une erreur est survenue: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
