#include "MultiBow.h"

MultiBow::MultiBow(int* player_arrows, float game_scale)
    :
    Bow(20.0f, 1, 30, "MultiBow", player_arrows, game_scale)
{    
    if (!bow_texture.loadFromFile("art/MultiBow.png")) {
		std::cout << "MultiBow texture could not be loaded!" << std::endl;
	}

	bow_sprite.setTexture(bow_texture, true);
	bow_sprite.setScale(sf::Vector2f(game_scale, game_scale));
    
    sf::Vector2f centre((float)bow_sprite.getTextureRect().width / 2, 
        (float)bow_sprite.getTextureRect().height / 2);

    bow_sprite.setOrigin(centre);

    for (int i = 0; i < 5; i++) {
        sprites.push_back(sf::Sprite(texture));

        sprites[i].setScale(sf::Vector2f(game_scale,game_scale));

        centre = sf::Vector2f((float)sprites[i].getTextureRect().width / 2, 
            (float)sprites[i].getTextureRect().height / 2);

        sprites[i].setOrigin(centre);
        

        arrow_velocities.push_back(sf::Vector2f(0.0f, 0.0f));

        sprite_active.push_back(false);
    }
}

void MultiBow::commenceAttack() {

    if (*player_arrows <= 0) {
        std::cout << "Can't attack, you have no arrows!" << std::endl;
        return;
    }

    *player_arrows = *player_arrows - 1;
    
    float spread = 20.0f;
    float angle = bow_sprite.getRotation() - spread;

    for (int i = 0; i < sprites.size(); i++) {
        sprites[i].setPosition(bow_sprite.getPosition());

        if (angle < 0.0f) {
            angle += 360.0f;
        }
        else if (angle > 360.0f) {
            angle -= 360.0f;
        }

        arrow_velocities[i] = calculateUnitVector(angle) * intial_arrow_speed;

        angle += spread / 2;
        sprite_active[i] = true;
    }

    is_attacking = true;
}

bool MultiBow::updateAttack() {
    
    bool are_arrows_inactive = true;

    for (int i = 0; i < sprites.size(); i++) {

        if (!sprite_active[i]) {
            continue;
        }
        are_arrows_inactive = false;

        arrow_velocities[i].y += 0.7;
        sprites[i].move(arrow_velocities[i]);

        float angle = calculateAngle(arrow_velocities[i], sf::Vector2f(0.0f, 0.0f));
        sprites[i].setRotation(angle);
    }

    return are_arrows_inactive;
}

void MultiBow::reset() {
    is_attacking = false;
}