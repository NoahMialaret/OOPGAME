#include "BroardSword.h"

BroardSword::BroardSword(float game_scale)
    :
    Melee(90.0f, 1, 100, "BroardSword", game_scale)
{    
    sprites.push_back(sf::Sprite(texture));

    sword = &sprites[0];

    sword->setScale(sf::Vector2f(game_scale,game_scale));

    sf::Vector2f centre((float)sword->getTextureRect().width / 2, 
        (float)sword->getTextureRect().height / 2);

    sword->setOrigin(centre);
    
    sprite_active.push_back(false);
}

void BroardSword::commenceAttack() {

    if (sword->getRotation() < 180.0f) {
        is_attacking_right = true; 
        end_angle = sword->getRotation() + swing_length;
    }
    else {
        is_attacking_right = false;
        end_angle = sword->getRotation() - swing_length;
    }
    std::cout << "Start angle: " << sword->getRotation() << " - End angle: " << end_angle << std::endl; 
    
    sprite_active[0] = true;

    is_attacking = true;
}

void BroardSword::updateWeapon(sf::Vector2f mouse_pos) {
    float cur_angle = calculateAngle(mouse_pos, centre_pos);

    if (cur_angle < 180.0f && cur_angle > 110.0f) {
        cur_angle = 110.0f;
    }
    else if (cur_angle > 180.0f && cur_angle < 250.0f) {
        cur_angle = 250.0f;
    } 

    sword->setRotation(cur_angle);

    sword->setPosition(centre_pos + calculateUnitVector(cur_angle) * 30.0f);
}

bool BroardSword::updateAttack() {

    sword->rotate(cur_swing_speed);

    sword->setPosition(centre_pos + calculateUnitVector(sword->getRotation()) * 30.0f);
        
    cur_swing_speed += is_attacking_right * 8.0f - !is_attacking_right * 8.0f;

    if ((is_attacking_right && sword->getRotation() > end_angle) || (!is_attacking_right && sword->getRotation() < end_angle)) {
        reset();
        return true;
    }

    return false;
}

void BroardSword::reset() {
    is_attacking = false;
    cur_swing_speed = 0.0f;
}