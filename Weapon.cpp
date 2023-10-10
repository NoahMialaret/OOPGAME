#include "Weapon.h"

Weapon::Weapon(int damage, int gold_cost, std::string name, float game_scale)
    :
    damage(damage),
    gold_cost(gold_cost),
    name(name),
    game_scale(game_scale)
{}

std::string Weapon::getName() {
    return name;
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
