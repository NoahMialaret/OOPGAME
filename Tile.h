#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"

class Tile {
private:
    int type = 0;

    sf::Sprite sprite;
public:
    Tile() = default;
    Tile(int type, float game_scale, float sprite_dim, sf::Vector2f pos, sf::Texture& sprite_sheet);
    //void update();
    void render(sf::RenderWindow* win) const;

    sf::Vector2f getPosition() const;
};

#endif