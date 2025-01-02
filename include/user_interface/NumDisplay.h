#ifndef NUMDISPLAY_H
#define NUMDISPLAY_H

#include "SFML/Graphics.hpp"

#include <iostream>

class NumDisplay
{
protected:

	sf::Texture numbers_tex;
	sf::Sprite numbers_sprite;
    sf::IntRect sprite_rect;

    // The integer value of the number being stored
    int count = 0;

    // A vector of int representing the digits of a number, in reverse
    std::vector<int> digits;
public:
    NumDisplay() = default;
    NumDisplay(int initial_value);
    void setSprite(float game_scale);

    void SetNumber(int number); // Changes the value of the number
    int GetNumber() const;      // Returns the currently stored number
    void AddNumber(int number); // Adds the specified amount to the number

    void render(sf::RenderWindow* win, sf::Vector2f centre_position); // Renders the number to the screen

};

#endif