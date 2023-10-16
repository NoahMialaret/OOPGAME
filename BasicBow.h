#ifndef BASICBOW_H
#define BASICBOW_H

#include "Bow.h"

class BasicBow : public Bow {
private:
    sf::Sprite* arrow = nullptr;
    sf::Vector2f* arrow_velocity = nullptr;
public:
    BasicBow(float game_scale);
    void commenceAttack() override;
    bool updateAttack() override;

    void reset() override;
};

#endif