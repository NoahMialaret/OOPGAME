#ifndef ENTITY_H
#define ENTITY_H

#include <algorithm>
#include <iostream>

#include "SFML/Graphics.hpp"

class Entity {
protected:
	sf::Vector2f velocity = sf::Vector2f(0.0f, 0.0f); // Vector representing the Entity's velocity

	sf::Texture tex;
	sf::Sprite sprite;

public:
    Entity(const char* tex_name, float game_scale, sf::Vector2f pos);
    void update(const sf::RenderWindow* win);
    void render(sf::RenderWindow* win) const;
};

#endif