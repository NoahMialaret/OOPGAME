#include "Entity.h"

Entity::Entity(const char *tex_name, float game_scale, sf::Vector2f pos)
{
    if (!tex.loadFromFile(tex_name)) {
		std::cout << "Entity texture (" << tex_name << ") could not be loaded!" << std::endl;
		return;
	}

	sprite.setTexture(tex, true);
	sprite.setScale(sf::Vector2f(game_scale, game_scale));

    sprite.setPosition(pos);
}

void Entity::render(sf::RenderWindow *win) const {
    win->draw(sprite);
}