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

void Entity::update() {
	// Effect of gravity on the entity
	velocity.y += 0.8f;

	sprite.move(velocity);
}

void Entity::render(sf::RenderWindow* win) const {
    win->draw(sprite);
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}

sf::IntRect Entity::getHitbox() const {
	sf::IntRect hitbox = sprite.getTextureRect();
	hitbox.top = sprite.getPosition().y;
	hitbox.left = sprite.getPosition().x;
	hitbox.height = hitbox.height * sprite.getScale().y;
	hitbox.width = hitbox.width * sprite.getScale().x;
    return hitbox;
}

sf::Vector2f Entity::getVelocity() const {
    return velocity;
}

void Entity::setVelocity(sf::Vector2f new_vel) {
	velocity = new_vel;
}

void Entity::move(sf::Vector2f offset) {
	sprite.move(offset);
}

void Entity::setGrounded(bool _is_grounded) {
	is_grounded = _is_grounded;
}

bool Entity::isGrounded() const {
    return is_grounded;
}

void Entity::setPosition(sf::Vector2f new_position) {
	sprite.setPosition(new_position);
}
