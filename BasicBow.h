#ifndef BASICBOW_H
#define BASICBOW_H

#include "Bow.h"

class BasicBow : public Bow {
private:
public:
    BasicBow(float game_scale);
    void commenceAttack(float initial_angle) override;
    void update(sf::Vector2f mouse_pos) override;
    void getSpritesForCollision() override;
};

#endif