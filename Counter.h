#ifndef COUNTER_H
#define COUNTER_H

#include "SFML/Graphics.hpp"

#include <iostream>

class Counter
{
public:
    Counter() = default;
    Counter(sf::Clock& clock, int initial_value);
    void setSprite(float game_scale);

    bool update(sf::Clock& clock); // Updates the counter using the amount of time since last updating
    void render(sf::RenderWindow* win, sf::Vector2f centre_position); // Renders the number to the screen
    void tick(); // Reduces the current count by 1

private:

	sf::Texture numbers_tex;
	sf::Sprite numbers_sprite;
    sf::IntRect sprite_rect;

    // The integer value of the number being stored
    int count = 0;

    // A vector of int representing the digits of a number, in reverse
    std::vector<int> digits;

    // Value representing the tick of the previous second update 
    int last_update_tick = 0;

};

#endif