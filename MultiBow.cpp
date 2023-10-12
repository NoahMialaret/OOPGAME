#include "MultiBow.h"

MultiBow::MultiBow(float game_scale)
    :
    Bow(20.0f, 1, 100, "Multi-Bow", game_scale)
{    
    if (!bow_texture.loadFromFile("art/MultiBow.png")) {
		std::cout << "MultiBow texture could not be loaded!" << std::endl;
	}

	bow_sprite.setTexture(bow_texture, true);
	bow_sprite.setScale(sf::Vector2f(game_scale, game_scale));
    
    sf::Vector2f centre((float)bow_sprite.getTextureRect().width / 2, 
        (float)bow_sprite.getTextureRect().height / 2 + 8.5f);

    std::cout << centre.x << " - " << centre.y << std::endl;

    bow_sprite.setOrigin(centre);

    for (int i = 0; i < 3; i++) {
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

    float spread = 10.0f;
    float angle = bow_sprite.getRotation() - spread;

    for (int i = 0; i < sprites.size(); i++) {
        sprites[i].setPosition(bow_sprite.getPosition());

        if (angle < 0.0f) {
            angle += 360.0f;
        }
        else if (angle > 360.0f) {
            angle -= 360.0f;
        }

        arrow_velocities[i] = calculateArrowVelocity(angle);
        angle += spread;
        sprite_active[i] = true;
    }

    is_attacking = true;
}

void MultiBow::updateWeapon(sf::Vector2f mouse_pos) {
    bow_sprite.setRotation(calculateAngle(mouse_pos, bow_sprite.getPosition()));
}

void MultiBow::updateAttack() {
    for (int i = 0; i < sprites.size(); i++) {
        arrow_velocities[i].y += 0.7;
        sprites[i].move(arrow_velocities[i]);

        float angle = calculateAngle(arrow_velocities[i], sf::Vector2f(0.0f, 0.0f));
        sprites[i].setRotation(angle);
    }
}

void MultiBow::reset() {
    is_attacking = false;
}