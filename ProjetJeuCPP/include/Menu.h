#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::Vector2u windowSize);
    void draw(sf::RenderWindow& window);
    bool isStartClicked(const sf::Vector2i& mousePos) const;
    bool isExitClicked(const sf::Vector2i& mousePos) const;
    void handleMouseHover(const sf::Vector2i& mousePos);


private:
    sf::Font font;
    sf::Text title;
    sf::Text start;
    sf::Text exit;
};

#endif // MENU_H
