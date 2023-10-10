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