#include "Weapon.h"

Weapon::Weapon(int damage, int gold_cost, std::string name, float game_scale)
    :
    damage(damage),
    gold_cost(gold_cost),
    name(name),
    game_scale(game_scale),
    centre_pos(sf::Vector2f(0.0f, 0.0f))
{}

std::vector<sf::Sprite> *Weapon::getSpritesForCollision() {
    return &sprites;
}

std::string Weapon::getName() {
    return name;
}

int Weapon::getDamage() const {
    return damage;
}

bool Weapon::isAttacking() {
    return is_attacking;
}

void Weapon::setCentrePosition(sf::Vector2f new_centre_pos) {
    centre_pos = new_centre_pos;
}

float Weapon::calculateAngle(sf::Vector2f mouse_pos, sf::Vector2f sprite_pos) const {
    float x_dif = mouse_pos.x - sprite_pos.x;
    float y_dif = mouse_pos.y - sprite_pos.y;

    if (y_dif >= 0) {
        if (x_dif == 0.0f) { // If dividing by 0
            x_dif++;
        }
        float angle_offset = x_dif >= 0 ? 90.0f : 270.0f;
        return angle_offset + (180.0f / 3.14f) * atan(y_dif / x_dif);
    }
    else {
        if (y_dif == 0.0f) { // If dividing by 0
            y_dif++;
        }
        float angle_offset = x_dif >= 0 ? 0.0f : 360.0f;
        return angle_offset - (180.0f / 3.14f) * atan(x_dif / y_dif);
    }
}

sf::Vector2f Weapon::calculateUnitVector(float angle) const {
    int quadrant = 0; // Top right cicle quadrant = 0, increases by one for every quadrant clockwise
    while(angle > 90.0f)
    {
        angle -= 90.0f;
        quadrant++;
    }

    float rad_angle = (3.14 / 180.0f) * (angle - 90.0f);

    sf::Vector2f unit_vector;
    if (quadrant % 2 == 0) {
        if (quadrant == 0) {
            unit_vector = sf::Vector2f(cos(rad_angle), sin(rad_angle));            
        }
        else {
            unit_vector = sf::Vector2f( - cos(rad_angle), - sin(rad_angle));            
        }
    }
    else {
        if (quadrant == 1) {
            unit_vector = sf::Vector2f( - sin(rad_angle), cos(rad_angle));            
        }
        else {
            unit_vector = sf::Vector2f( sin(rad_angle), - cos(rad_angle));            
        }
    }

    return unit_vector;
}
