#include "BasicBow.h"

BasicBow::BasicBow(float game_scale)
    :
    Bow(10.0f, 1, 100, "Basic Bow", game_scale)
{    
    if (!bow_texture.loadFromFile("art/BasicBow.png")) {
		std::cout << "BasicBow texture could not be loaded!" << std::endl;
	}

	bow_sprite.setTexture(bow_texture, true);
	bow_sprite.setScale(sf::Vector2f(game_scale, game_scale));
    
    sf::Vector2f centre((float)bow_sprite.getTextureRect().width / 2, 
        (float)bow_sprite.getTextureRect().height / 2 + 8.5f);

    std::cout << centre.x << " - " << centre.y << std::endl;

    bow_sprite.setOrigin(centre);
    bow_sprite.move(sf::Vector2f(100.0f, 0.0f));
}

void BasicBow::commenceAttack(float initial_angle) {    
    sprites.push_back(sf::Sprite(texture));
    sprites[0].setRotation(bow_sprite.getRotation());

    is_attacking = true;
}

void BasicBow::update(sf::Vector2f mouse_pos) {
    if (is_attacking) {
        sprites[0].move(sf::Vector2f(1.0f, 0.0f));
    }

    bow_sprite.setRotation(calculateAngle(mouse_pos, bow_sprite.getPosition()));
}

void BasicBow::getSpritesForCollision() {
}
