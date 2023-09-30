#ifndef ENTITY_H
#define ENTITY_H

#include <algorithm>
#include <iostream>

#include "SFML/Graphics.hpp"

class Entity {
protected:
	sf::Texture tex;
	sf::Sprite sprite;

public:
    Entity(const char* tex_name, float game_scale);
    void render(sf::RenderWindow* win) const;
};

#endif