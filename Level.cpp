#include "Level.h"

Level::Level(float game_scale, float sprite_dim) {

	if (!sprite_sheet.loadFromFile("art/TestTile.png")) {
		std::cout << "Level sprite sheet could not be loaded! Loading default level without textures." << std::endl;
        loadDefaultLevel(game_scale, sprite_dim);
		return;
	}

    std::ifstream file("files/level_1.txt");

	if (!file) {
		std::cout << "Could not open level file, loading default level" << std::endl;
		loadDefaultLevel(game_scale, sprite_dim);
		return;
	}

	std::string fileline;
    int y = -1;

    while(std::getline(file, fileline)) {
        if (dim.y != 0 && fileline.size() != dim.x) {
            std::cout << "Row widths did not match, loading default level." << std::endl;
            loadDefaultLevel(game_scale, sprite_dim);
            return;
        }

        y++;

        dim.x = fileline.size();

        for(int x = 0; x < fileline.size(); x++) {
            int type = fileline[x] - 48;

            if(type < (int)TileType::empty || type >= (int)TileType::end) {
                std::cout << "Attempted to access non-existent TileType, loading default level." << std::endl;
                loadDefaultLevel(game_scale, sprite_dim);
                return;
            }

            tiles.push_back(Tile(type, game_scale, sprite_dim, sf::Vector2f(float(x) * sprite_dim * game_scale, 
                float(y) * sprite_dim * game_scale), sprite_sheet));
        }

    }

    dim.y = y;
}

void Level::loadDefaultLevel(float game_scale, float sprite_dim) {
	tiles.clear();
	dim.x = 5;
	dim.y = 5;
	for (int y = 0; y < dim.y; y++)	{
		for (int x = 0; x < dim.x; x++) {
            int type = 0;
			if (y == 2) {
                type = 1;
			}
			else if (y > 2) {
                type = 2;
            }
            tiles.push_back(Tile(type, game_scale, sprite_dim, sf::Vector2f(float(x) * sprite_dim * game_scale, 
                float(y) * sprite_dim * game_scale), sprite_sheet));
		}
	}
}

void Level::render(sf::RenderWindow* win) const {
    for (auto& t : tiles) {
        t.render(win);
    }
}

Tile &Level::getTile(sf::Vector2i tile_pos) {
    return tiles[tile_pos.y * dim.x + tile_pos.x];
}