#include "Melee.h"

Melee::Melee(float swing_length, int damage, int gold_cost, std::string name, float game_scale)
    :
    Weapon(damage, gold_cost, name, game_scale),
    swing_length(swing_length)
{
    if (!texture.loadFromFile("art/" + name + ".png")) {
		std::cout << name << " texture could not be loaded!" << std::endl;
	}
}

void Melee::render(sf::RenderWindow* win) {
    for (auto& s : sprites) {
        win->draw(s);
    }
}