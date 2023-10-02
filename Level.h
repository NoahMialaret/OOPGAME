#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"

#include "SFML/Graphics.hpp"

#include <assert.h>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

class Level {
public:
    enum class TileType {
        empty,
        grass,
        ground,
        end
    };
private:
    std::vector<Tile> tiles;

    sf::Texture sprite_sheet;

    sf::Vector2i dim = sf::Vector2i(0, 0);
public:
    Level(float game_scale, float sprite_dim);
    void loadDefaultLevel(float game_scale, float sprite_dim);
    void render(sf::RenderWindow* win) const;

    std::vector<int> getSurroundingCollision(sf::Vector2i grid_pos);

    sf::Vector2i getLevelDim() const;
    sf::Vector2i getValidSpawnPos(std::mt19937& rng) const;
    Tile& getTile(sf::Vector2i tile_pos);
    const int getTileType(sf::Vector2i tile_pos) const;
};

#endif