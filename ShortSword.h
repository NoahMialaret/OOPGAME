#ifndef SHORTSWORD_H
#define SHORTSWORD_H

#include "Melee.h"

class ShortSword : public Melee {
private:
    float stab_offset = 0.0f;
    float stab_velocity = 0.0f;
    sf::Sprite* sword = nullptr;
public:
    ShortSword(float game_scale);
    void commenceAttack() override;
    void updateWeapon(sf::Vector2f mouse_pos) override;
    bool updateAttack() override;

    void reset() override;
};

#endif