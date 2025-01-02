#include "Bow.h"

Bow::Bow(float speed, int damage, int gold_cost, std::string name, int* player_arrows, float game_scale)
    :
    Weapon(damage, gold_cost, name, game_scale),
    intial_arrow_speed(speed),
    player_arrows(player_arrows)
{
    if (!texture.loadFromFile("art/Arrow.png")) {
		std::cout << "Arrow texture could not be loaded!" << std::endl;
	}
}

void Bow::updateWeapon(sf::Vector2f mouse_pos) {
    bow_sprite.setRotation(calculateAngle(mouse_pos, centre_pos));

    bow_sprite.setPosition(centre_pos + calculateUnitVector(bow_sprite.getRotation()) * 30.0f);
}

void Bow::render(sf::RenderWindow *win) {
    if (is_attacking) {
        for (int i = 0; i < sprites.size(); i++) {
            if (sprite_active[i]) {
                win->draw(sprites[i]);
            }
        }
    }

    win->draw(bow_sprite);
}