#include "Entity.h"

Entity::Entity(const char *tex_name, float game_scale) {
	if (!tex.loadFromFile("art/TestCharacter.png")) {
		std::cout << "Entity texture could not be loaded!" << std::endl;
		return;
	}

	sprite.setTexture(tex, true);
	sprite.setScale(sf::Vector2f(game_scale, game_scale));
}

void Entity::render(sf::RenderWindow *win) const {
    win->draw(sprite);
}