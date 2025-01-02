#include "NumDisplay.h"

NumDisplay::NumDisplay(int initial_value) {
    if (!numbers_tex.loadFromFile("art/Numbers.png")) {
		std::cout << "NumDisplay texture could not be loaded!" << std::endl;
		return;
	}

    if (initial_value < 0) {
        std::cout << "Warning, initial count value was set to less than zero." << std::endl;
        count = 0;

        digits.clear();
        digits.push_back(0);

        return;
    }

    digits.push_back(0);
    AddNumber(initial_value);
    
}

void NumDisplay::setSprite(float game_scale) {
	numbers_sprite.setScale(sf::Vector2f(game_scale * 2.0f, game_scale * 2.0f));

    sprite_rect = sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(5, 7));
    numbers_sprite.setTextureRect(sprite_rect);

	numbers_sprite.setTexture(numbers_tex);
}

void NumDisplay::SetNumber(int newNumber)
{
    AddNumber(newNumber - count);
}

int NumDisplay::GetNumber() const
{
    return count;
}

void NumDisplay::AddNumber(int addition)
{
    count += addition;

    if (count < 0)
    {
        count = 0;

        digits.clear();
        digits.push_back(0);

        return;
    }

    bool carry = false;
    int sign = addition >= 0 ? 1 : -1;

    addition = abs(addition);

    for (int i = 0; i < digits.size(); i++)
    {
        digits[i] += sign * (addition % 10 + (int)carry);
        
        if (digits[i] >= 10 || digits[i] < 0)
        {
            digits[i] -= sign * 10;
            carry = true;
            addition /= 10;
            continue;
        }

        carry = false;
        addition /= 10;
    }

    while(addition != 0 || carry)
    {
        digits.push_back(addition % 10 + (int)carry);
        carry = false;
        addition /= 10;
    }

    for (int i = digits.size() - 1; i > 0; i--)
    {
        if (digits[i] != 0)
        {
            break;
        }

        digits.pop_back();
    }
}

void NumDisplay::render(sf::RenderWindow* win, sf::Vector2f centre_position) {
    numbers_sprite.setPosition(centre_position);

    for (int i = digits.size() - 1; i >= 0; i--) {
        sprite_rect.left = sprite_rect.width * digits[i];
        numbers_sprite.setTextureRect(sprite_rect);
        win->draw(numbers_sprite);
        numbers_sprite.move(sf::Vector2f((float)sprite_rect.width * numbers_sprite.getScale().x, 0.0f));
    }
}