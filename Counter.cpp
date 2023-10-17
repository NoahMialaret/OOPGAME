#include "Counter.h"

Counter::Counter(sf::Clock* clock, int initial_value)
    :
    NumDisplay(initial_value),
    last_update_tick(clock->getElapsedTime().asMilliseconds())
{}

bool Counter::update(sf::Clock* clock)
{
    while (last_update_tick + 1000 < clock->getElapsedTime().asMilliseconds()) {

        if (tick()) {
            return true;
        }

        last_update_tick += 1000;
    }

    return false;
}

bool Counter::tick() {
    if (count == 0) {
        std::cout << "Out of time!" << std::endl;
        return true;
    }

    AddNumber(-1);

    std::cout << "Tick! counter now at " << count << std::endl;
    return false;
}
