#include "Bow.h"

Bow::Bow(float speed, int damage, int gold_cost, std::string name, float game_scale)
    :
    Weapon(damage, gold_cost, name, game_scale),
    intial_arrow_speed(speed)
{
    if (!texture.loadFromFile("art/Arrow.png")) {
		std::cout << "Arrow texture could not be loaded!" << std::endl;
	}
}

void Bow::render(sf::RenderWindow *win) {
    if (is_attacking)
    {
        for (auto& arrow : sprites)
        {
            win->draw(arrow);
        }
    }

    win->draw(bow_sprite);
}

void Bow::drawWeapon(sf::Vector2f centre_pos) {
    bow_sprite.setPosition(centre_pos);
}

sf::Vector2f Bow::calculateArrowVelocity(float angle)
{
    int quadrant = 0; // Top right cicle quadrant = 0, increases by one for every quadrant clockwise
    while(angle > 90.0f)
    {
        angle -= 90.0f;
        quadrant++;
    }

    float rad_angle = (3.14 / 180.0f) * (angle - 90.0f);

    sf::Vector2f velocity;
    if (quadrant % 2 == 0) {
        if (quadrant == 0) {
            velocity = sf::Vector2f(cos(rad_angle) * intial_arrow_speed, sin(rad_angle) * intial_arrow_speed);            
        }
        else {
            velocity = sf::Vector2f( - cos(rad_angle) * intial_arrow_speed, - sin(rad_angle) * intial_arrow_speed);            
        }
    }
    else {
        if (quadrant == 1) {
            velocity = sf::Vector2f( - sin(rad_angle) * intial_arrow_speed, cos(rad_angle) * intial_arrow_speed);            
        }
        else {
            velocity = sf::Vector2f( sin(rad_angle) * intial_arrow_speed, - cos(rad_angle) * intial_arrow_speed);            
        }
    }

    return velocity;
}
