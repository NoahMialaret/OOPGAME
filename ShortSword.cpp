#include "ShortSword.h"

ShortSword::ShortSword(float game_scale)
    :
    Melee(0.0f, 1, 100, "ShortSword", game_scale)
{    
    sprites.push_back(sf::Sprite(texture));

    sword = &sprites[0];

    sword->setScale(sf::Vector2f(game_scale,game_scale));

    sf::Vector2f centre((float)sword->getTextureRect().width / 2, 
        (float)sword->getTextureRect().height / 2);

    sword->setOrigin(centre);
    
    sprite_active.push_back(false);
}

void ShortSword::commenceAttack() {

    stab_velocity = 5.0f;

    sprite_active[0] = true;

    is_attacking = true;
}

void ShortSword::updateWeapon(sf::Vector2f mouse_pos) {
    float cur_angle = calculateAngle(mouse_pos, centre_pos);

    sword->setRotation(cur_angle);

    sword->setPosition(centre_pos + calculateUnitVector(cur_angle) * 30.0f);
}

bool ShortSword::updateAttack() {

    stab_offset += stab_velocity;

    stab_velocity -= 1.0f;
    
    float offset = 30.0f + stab_offset;

    if (offset < 30.0f) {
        reset();
        return true;
    }

    sword->setPosition(centre_pos + calculateUnitVector(sword->getRotation()) * offset);
        
    return false;
}

void ShortSword::reset() {
    is_attacking = false;
    stab_offset = 0.0f;
    stab_velocity = 0.0f;
}