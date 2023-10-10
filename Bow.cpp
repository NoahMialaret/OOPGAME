#include "Bow.h"

Bow::Bow(float range, int damage, int gold_cost, std::string name, float game_scale)
    :
    Weapon(damage, gold_cost, name, game_scale)
{
    if (!texture.loadFromFile("art/Arrow.png")) {
		std::cout << "Arrow texture could not be loaded!" << std::endl;
	}
}

void Bow::render(sf::RenderWindow *win) {
    for (auto& arrow : sprites)
    {
        win->draw(arrow);
    }

    win->draw(bow_sprite);
}

void Bow::drawWeapon(sf::Vector2f centre_pos) {
    bow_sprite.setPosition(centre_pos);
}
