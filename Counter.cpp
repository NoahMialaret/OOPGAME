#include "Counter.h"

Counter::Counter(sf::Clock* clock, int initial_value)
    :
    NumDisplay(initial_value),
    last_update_tick(clock->getElapsedTime().asMilliseconds())
{}

bool Counter::update(sf::Clock* clock)
{
    while (last_update_tick + 1000 < clock->getElapsedTime().asMilliseconds()) {
        tick();

        if (count < 0) {
            return true;
        }

        last_update_tick += 1000;
    }

    return false;
}

void Counter::tick() {
    count--;

    std::cout << "Tick! counter now at " << count << std::endl;

    for (int i = digits.size() - 1; i >= 0; i++) {
        digits[i]--;
        if (digits[i] < 0) {
            digits[i] = 9;
            continue;
        }
        break;
    }
}
