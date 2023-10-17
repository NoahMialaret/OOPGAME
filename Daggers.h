#ifndef DAGGERS_H
#define DAGGERS_H

#include "Melee.h"

class Daggers : public Melee {
private:
    float end_angle = 0.0f;
    float cur_swing_speed = 0.0f;
public:
    Daggers(float game_scale);
    void commenceAttack() override;
    void updateWeapon(sf::Vector2f mouse_pos) override;
    bool updateAttack() override;

    void reset() override;
};

#endif