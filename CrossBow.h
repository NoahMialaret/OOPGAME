#ifndef CROSSBOW_H
#define CROSSBOW_H

#include "Bow.h"

class CrossBow : public Bow {
private:
    sf::Sprite* arrow = nullptr;
    sf::Vector2f* arrow_velocity = nullptr;
public:
    CrossBow(float game_scale);
    void commenceAttack() override;
    void updateWeapon(sf::Vector2f mouse_pos) override;
    void updateAttack() override;

    void reset() override;
};

#endif