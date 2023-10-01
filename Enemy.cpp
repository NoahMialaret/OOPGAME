#include "Enemy.h"

Enemy::Enemy(const char *tex_name, float game_scale, sf::Vector2u level_bounds)
    :
    Entity(tex_name, game_scale, sf::Vector2f(0.0f, 0.0f)),
    rng(std::random_device()())
{
    std::uniform_int_distribution<int> x_dist(0, level_bounds.x - sprite.getScale().x * sprite.getTexture()->getSize().x);
    std::uniform_int_distribution<int> y_dist(0, level_bounds.y - sprite.getScale().y * sprite.getTexture()->getSize().y);

    sprite.setPosition(sf::Vector2f((float)x_dist(rng), (float)y_dist(rng)));
}

void Enemy::update(const sf::RenderWindow* win) {
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

sf::Vector2f Enemy::teleport(const sf::Vector2u& level_bounds)
{
    std::uniform_int_distribution<int> x_dist(0, level_bounds.x - sprite.getScale().x * sprite.getTexture()->getSize().x);
    std::uniform_int_distribution<int> y_dist(0, level_bounds.y - sprite.getScale().y * sprite.getTexture()->getSize().y);

    sprite.setPosition(sf::Vector2f((float)x_dist(rng), (float)y_dist(rng)));

    return sprite.getPosition();
}
