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
    void update(sf::Vector2f mouse_pos) override;
    void getSpritesForCollision() override;

    void reset() override;
};

#endif