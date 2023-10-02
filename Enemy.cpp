#include "Enemy.h"

Enemy::Enemy(const char *tex_name, float game_scale)
    :
    Entity(tex_name, game_scale, sf::Vector2f(0.0f, 0.0f))
{}

void Enemy::teleport(sf::Vector2f new_pos)
{
    sprite.setPosition(new_pos);
}