#include "Entity.h"

Entity::Entity(const char *tex_name, float game_scale, sf::Vector2f pos) {
    if (!tex.loadFromFile(tex_name)) {
		std::cout << "Entity texture (" << tex_name << ") could not be loaded!" << std::endl;
		return;
	}

	sprite.setTexture(tex, true);
	sprite.setScale(sf::Vector2f(game_scale, game_scale));

    sprite.setPosition(pos);
}

void Entity::update(const sf::RenderWindow* win) {
	// Effect of gravity on the enemy
	velocity.y += 0.8f;

	sprite.move(velocity);

	if (sprite.getPosition().y > (float)win->getSize().y - sprite.getScale().y * sprite.getTextureRect().height) {
		velocity.y = 0.0f;
	}

	sf::Vector2f pos(sprite.getPosition().x, 0.0f);
	pos.y = std::clamp(sprite.getPosition().y, 0.0f, (float)win->getSize().y - sprite.getScale().y * sprite.getTextureRect().height);
	sprite.setPosition(pos);
}

void Entity::render(sf::RenderWindow* win) const {
    win->draw(sprite);
}