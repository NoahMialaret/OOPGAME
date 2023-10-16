#include "CrossBow.h"

CrossBow::CrossBow(int* player_arrows, float game_scale)
    :
    Bow(25.0f, 1, 100, "CrossBow", player_arrows, game_scale)
{    
    if (!bow_texture.loadFromFile("art/CrossBow.png")) {
		std::cout << "CrossBow texture could not be loaded!" << std::endl;
	}

	bow_sprite.setTexture(bow_texture, true);
	bow_sprite.setScale(sf::Vector2f(game_scale, game_scale));
    
    sf::Vector2f centre((float)bow_sprite.getTextureRect().width / 2, 
        (float)bow_sprite.getTextureRect().height / 2);

    bow_sprite.setOrigin(centre);


    sprites.push_back(sf::Sprite(texture));

    arrow = &sprites[0];

    arrow->setScale(sf::Vector2f(game_scale,game_scale));

    centre = sf::Vector2f((float)arrow->getTextureRect().width / 2, 
        (float)arrow->getTextureRect().height / 2);

    arrow->setOrigin(centre);
    

    arrow_velocities.push_back(sf::Vector2f(0.0f, 0.0f));
    arrow_velocity = &arrow_velocities[0];

    sprite_active.push_back(false);
}

void CrossBow::commenceAttack() {

    if (*player_arrows <= 0) {
        std::cout << "Can't attack, you have no arrows!" << std::endl;
        return;
    }
    
    *player_arrows = *player_arrows - 1;

    arrow->setPosition(bow_sprite.getPosition());

    *arrow_velocity = calculateUnitVector(bow_sprite.getRotation()) * intial_arrow_speed;
    
    sprite_active[0] = true;

    is_attacking = true;
}

bool CrossBow::updateAttack() {

    if (!sprite_active[0]) {
        return true;
    }

    arrow_velocity->y += 0.2;
    arrow->move(*arrow_velocity);

    float angle = calculateAngle(*arrow_velocity, sf::Vector2f(0.0f, 0.0f));
    arrow->setRotation(angle);

    return false;
}

void CrossBow::reset() {
    is_attacking = false;
}