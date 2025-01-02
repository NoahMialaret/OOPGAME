#ifndef MELEE_H
#define MELEE_H

#include "SFML/Graphics.hpp"

#include "Weapon.h"

class Melee : public Weapon {
protected:
    float swing_length = 0.0f;
public:
    Melee(float swing_length, int damage, int gold_cost, std::string name, float game_scale);
    void render(sf::RenderWindow* win) override;
};

#endif