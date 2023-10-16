#include "Level.h"

Level::Level(float game_scale, float sprite_dim) {

	if (!sprite_sheet.loadFromFile("art/Tiles.png")) {
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

    dim.y = -1;

    while(std::getline(file, fileline)) {
        dim.y++;

        if (dim.y > 0 && fileline.size() != dim.x) {
            std::cout << "Row widths did not match, loading default level." << std::endl;
            loadDefaultLevel(game_scale, sprite_dim);
            return;
        }

        dim.x = fileline.size();

        for(int x = 0; x < fileline.size(); x++) {
            int type = fileline[x] - 48;

            if(type < (int)TileType::empty || type >= (int)TileType::end) {
                std::cout << "Attempted to access non-existent TileType, loading default level." << std::endl;
                loadDefaultLevel(game_scale, sprite_dim);
                return;
            }

            tiles.push_back(Tile(type, game_scale, sprite_dim, sf::Vector2f(float(x) * sprite_dim * game_scale, 
                float(dim.y) * sprite_dim * game_scale), sprite_sheet));
        }

    }
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

std::vector<int> Level::getSurroundingCollision(sf::Vector2i grid_pos) {
    std::vector<int> col;
    std::vector<int> type;
    type.push_back(getTileType(grid_pos));
    type.push_back(getTileType(grid_pos + sf::Vector2i(1,0)));
    type.push_back(getTileType(grid_pos + sf::Vector2i(1,1)));
    type.push_back(getTileType(grid_pos + sf::Vector2i(0,1)));

    col.push_back((int)(type[0] > 0) - (int)(type[1] > 0));
    col.push_back((int)(type[1] > 0) - (int)(type[2] > 0));
    col.push_back(0 - (int)(type[2] > 0) + (int)(type[3] > 0));
    col.push_back(0 - (int)(type[3] > 0) + (int)(type[0] > 0));

    return col;
}

sf::Vector2i Level::getLevelDim() const {
    return dim;
}

sf::Vector2i Level::getValidSpawnPos(std::mt19937& rng) const {
    std::uniform_int_distribution<int> x_dist(0, dim.x);
    std::uniform_int_distribution<int> y_dist(0, dim.y);

    while(true) {
        sf::Vector2i random_pos = sf::Vector2i(x_dist(rng), y_dist(rng));
        if (getTileType(random_pos) == 0 && getTileType(random_pos + sf::Vector2i(0, 1)) > 0) {
            return random_pos;
        }
    }
}

Tile &Level::getTile(sf::Vector2i tile_pos) {
    assert(tile_pos.x >= 0 || tile_pos.y >= 0 || tile_pos.x < dim.x || tile_pos.y < dim.y);
    return tiles[tile_pos.y * dim.x + tile_pos.x];
}

const int Level::getTileType(sf::Vector2i tile_pos) const {
    if (tile_pos.x < 0 || tile_pos.x >= dim.x) {
        return (int)TileType::ground;
    }
    if (tile_pos.y < 0 || tile_pos.y >= dim.y) {
        return (int)TileType::empty;
    }
    return tiles[tile_pos.y * dim.x + tile_pos.x].getType();
}
