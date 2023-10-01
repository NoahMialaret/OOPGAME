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

sf::Vector2f Enemy::teleport(const sf::Vector2u& level_bounds) {
    std::uniform_int_distribution<int> x_dist(0, level_bounds.x - sprite.getScale().x * sprite.getTexture()->getSize().x);
    std::uniform_int_distribution<int> y_dist(0, level_bounds.y - sprite.getScale().y * sprite.getTexture()->getSize().y);

    sprite.setPosition(sf::Vector2f((float)x_dist(rng), (float)y_dist(rng)));

    return sprite.getPosition();
}
