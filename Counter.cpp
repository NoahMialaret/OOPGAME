#include "Counter.h"

Counter::Counter(sf::Clock& clock, int initial_value, float game_scale)
    :
    count(initial_value),
    last_update_tick(clock.getElapsedTime().asMilliseconds())
{
    if (initial_value < 0) {
        std::cout << "Warning, initial counter value was set to less than zero." << std::endl;
        count = 0;

        digits.clear();
        digits.push_back(0);

        return;
    }

    int digit = initial_value;

    while (digit != 0) {
        digits.push_back(digit % 10);
        digit /= 10;
    }
    
    if (!numbers_tex.loadFromFile("art/Numbers.png")) {
		std::cout << "Counter texture could not be loaded!" << std::endl;
		return;
	}

	numbers_sprite.setScale(sf::Vector2f(game_scale * 2.0f, game_scale * 2.0f));

    sprite_rect = sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(5, 7));
    numbers_sprite.setTextureRect(sprite_rect);


    sf::Vector2f centre((float)numbers_sprite.getTextureRect().width / 2, 
        (float)numbers_sprite.getTextureRect().height / 2);

    numbers_sprite.setOrigin(centre);
}

bool Counter::update(sf::Clock &clock) {

    while (last_update_tick + 1000 < clock.getElapsedTime().asMilliseconds()) {
        tick();

        if (count < 0) {
            return true;
        }

        last_update_tick += 1000;
    }

    return false;
}

void Counter::render(sf::RenderWindow* win, sf::Vector2f centre_position) {
	numbers_sprite.setTexture(numbers_tex);
    numbers_sprite.setPosition(centre_position);

    for (int i = 0; i < digits.size(); i++) {
        sprite_rect.left = sprite_rect.width * digits[i];
        numbers_sprite.setTextureRect(sprite_rect);
        win->draw(numbers_sprite);
        numbers_sprite.move(sf::Vector2f((float)sprite_rect.width * numbers_sprite.getScale().x, 0.0f));
    }
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
