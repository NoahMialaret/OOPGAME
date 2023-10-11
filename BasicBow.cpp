#include "BasicBow.h"

BasicBow::BasicBow(float game_scale)
    :
    Bow(25.0f, 1, 100, "Basic Bow", game_scale)
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


    sprites.push_back(sf::Sprite(texture));

    arrow = &sprites[0];

    arrow->setScale(sf::Vector2f(game_scale,game_scale));

    centre = sf::Vector2f((float)arrow->getTextureRect().width / 2, 
        (float)arrow->getTextureRect().height / 2);

    arrow->setOrigin(centre);
    

    arrow_velocities.push_back(sf::Vector2f(0.0f, 0.0f));
    arrow_velocity = &arrow_velocities[0];
}

void BasicBow::commenceAttack() {  
    arrow->setPosition(bow_sprite.getPosition());

    *arrow_velocity = calculateArrowVelocity(bow_sprite.getRotation());

    is_attacking = true;
}

void BasicBow::update(sf::Vector2f mouse_pos) {

    if (is_attacking) {
        arrow_velocities[0].y += 0.7;
        arrow->move(arrow_velocities[0]);

        float angle = calculateAngle(arrow_velocities[0], sf::Vector2f(0.0f, 0.0f));
        arrow->setRotation(angle);
    }
    else {
        bow_sprite.setRotation(calculateAngle(mouse_pos, bow_sprite.getPosition()));
    }
}

void BasicBow::getSpritesForCollision() {
}

void BasicBow::reset() {
    is_attacking = false;
}