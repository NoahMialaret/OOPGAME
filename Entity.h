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

    bool is_grounded = false; // Boolean representing whether the entity is grouned, used for jumping and animations

public:
    Entity(const char* tex_name, float game_scale, sf::Vector2f pos);
    void update(const sf::RenderWindow* win);
    virtual void render(sf::RenderWindow* win) const;

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    virtual void setVelocity(sf::Vector2f new_vel);
    void move(sf::Vector2f offset);
    void setGrounded(bool is_grounded);
};

#endif