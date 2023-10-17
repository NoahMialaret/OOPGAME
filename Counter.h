#ifndef COUNTER_H
#define COUNTER_H

#include "NumDisplay.h"

class Counter : public NumDisplay {
private:
    // Value representing the tick of the previous second update 
    int last_update_tick = 0;

public:
    Counter() = default;
    Counter(sf::Clock* clock, int initial_value);
    void tick(); // Reduces the current count by 1
    bool update(sf::Clock* clock); // Updates the counter using the amount of time since last updating
};

#endif