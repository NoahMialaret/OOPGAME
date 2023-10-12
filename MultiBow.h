#ifndef MULTIBOW_H
#define MULTIBOW_H

#include "Bow.h"

class MultiBow : public Bow {
public:
    MultiBow(float game_scale);
    void commenceAttack() override;
    void updateWeapon(sf::Vector2f mouse_pos) override;
    void updateAttack() override;

    void reset() override;
};

#endif