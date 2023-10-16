#include "Enemy.h"

Enemy::Enemy(const char *tex_name, float game_scale)
    :
    Entity(tex_name, game_scale, sf::Vector2f(0.0f, 0.0f))
{}

void Enemy::update(sf::Clock *clock) {

    if (!is_attacking) {
        // Effect of gravity on the enemy
        velocity.y += 0.8f;
    }
    if (is_attacking ) {
        velocity.x += velocity.x > 0 ? -0.05f : 0.05f;
        velocity.y += velocity.y > 0 ? -0.05f : 0.05f;
        if (attack_start_time + 2500 < clock->getElapsedTime().asMilliseconds()) {
            is_attacking = false;
            velocity.x = 0.0f;
            velocity.y = 0.0f;
        }
    }

	sprite.move(velocity);
}

void Enemy::teleport(sf::Vector2f new_pos) {
    sprite.setPosition(new_pos);
}

void Enemy::takeDamage(int damage_amount) {
    health -= damage_amount;
}

void Enemy::startAttack(sf::Vector2f start_pos, sf::Vector2f new_velocity, sf::Clock *clock) {
    is_attacking = true;
    attack_start_time = clock->getElapsedTime().asMilliseconds();

    sprite.setPosition(start_pos);
    velocity = new_velocity;
}

int Enemy::getHealth() const {
    return health;
}

bool Enemy::isAttacking() const {
    return is_attacking;
}
