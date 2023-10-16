#ifndef MULTIBOW_H
#define MULTIBOW_H

#include "Bow.h"

class MultiBow : public Bow {
public:
    MultiBow(int* player_arrows, float game_scale);
    void commenceAttack() override;
    bool updateAttack() override;

    void reset() override;
};

#endif