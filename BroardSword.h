#ifndef BROARDSWORD_H
#define BROARDSWORD_H

#include "Melee.h"

class BroardSword : public Melee {
private:
    float end_angle = 0.0f;
    float cur_swing_speed = 0.0f;
    bool is_attacking_right = false;
    sf::Sprite* sword = nullptr;
public:
    BroardSword(float game_scale);
    void commenceAttack() override;
    void updateWeapon(sf::Vector2f mouse_pos) override;
    bool updateAttack() override;

    void reset() override;
};

#endif