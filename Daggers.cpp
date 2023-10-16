#include "Daggers.h"

Daggers::Daggers(float game_scale)
    :
    Melee(60.0f, 1, 100, "Daggers", game_scale)
{    
    for (int i = 0; i < 2; i++) {
        sprites.push_back(sf::Sprite(texture));

        sprites[i].setScale(sf::Vector2f(game_scale,game_scale));

        sf::Vector2f centre((float)sprites[i].getTextureRect().width / 2, 
            (float)sprites[i].getTextureRect().height / 2);

        sprites[i].setOrigin(centre);
        
        sprite_active.push_back(false);
    }
}

void Daggers::commenceAttack() {

    end_angle = sprites[0].getRotation() + swing_length;
    sprite_active[0] = true;
    sprite_active[1] = true;

    is_attacking = true;
}

void Daggers::updateWeapon(sf::Vector2f mouse_pos) {
    float cur_angle = calculateAngle(mouse_pos, centre_pos);
    
    if (cur_angle > 180.0f) {
        cur_angle = 360.0f - cur_angle;
    }

    if (cur_angle < 180.0f && cur_angle > 110.0f) {
        cur_angle = 110.0f;
    }
    
    //std::cout << cur_angle << std::endl;

    sprites[0].setRotation(cur_angle);
    sprites[1].setRotation( - cur_angle);

    sprites[0].setPosition(centre_pos + calculateUnitVector(cur_angle) * 30.0f);
    sprites[1].setPosition(centre_pos + calculateUnitVector(sprites[1].getRotation()) * 30.0f);
}

bool Daggers::updateAttack() {

    sprites[0].rotate(cur_swing_speed);
    sprites[1].rotate( - cur_swing_speed);

    sprites[0].setPosition(centre_pos + calculateUnitVector(sprites[0].getRotation()) * 30.0f);
    sprites[1].setPosition(centre_pos + calculateUnitVector(sprites[1].getRotation()) * 30.0f);
        
    cur_swing_speed += 8.0f;

    if ((sprites[0].getRotation() > end_angle)) {
        reset();
        return true;
    }

    return false;
}

void Daggers::reset() {
    is_attacking = false;
    cur_swing_speed = 0.0f;
}