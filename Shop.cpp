#include "Shop.h"

Shop::Shop(std::mt19937 &rng, Player* player, int* player_arrows, float game_scale)
    :
    shop_list(),
    player(player)
{
    shop_list.setText(game_scale);
    std::uniform_int_distribution<int> weapon_dist(0, 4);
    switch (weapon_dist(rng)) {
        case 0:
            weapon = new BasicBow(player_arrows, game_scale);
            break;
        case 1:
            weapon = new MultiBow(player_arrows, game_scale);
            break;
        case 2:
            weapon = new CrossBow(player_arrows, game_scale);
            break;
        case 3:
            weapon = new BroardSword(game_scale);
            break;
        case 4:
            weapon = new Daggers(game_scale);
            break;
    }

    std::vector<std::string> shop_strings ={"Health potion - 10", "Speed potion - 15"};

    std::string cost = intToString(weapon->getCost());

    shop_strings.push_back({weapon->getName() + " - " + cost});

    shop_list.makeList(shop_strings, sf::Vector2f(100.0f, 200.0f));
}

Shop::~Shop() {
    if (!has_bought_weapon) {
        delete weapon;
    }
}

std::string Shop::intToString(int number) {
	std::string RevInt;

	while (number > 10) {
		RevInt.push_back((number % 10) + 48);
		number = number / 10; 
	}
	RevInt.push_back(number + 48);

	std::string stringedInt = "";

	for (auto i = RevInt.end(); i != RevInt.begin();)
	{
		i--;
		stringedInt.push_back(*i);
	}

	return stringedInt;
}

void Shop::update(sf::Vector2f mouse_pos, bool is_mouse_pressed) {
    
    int index = shop_list.update(mouse_pos);

    if (is_mouse_pressed) {
        switch (index)
        {
        case 2: // Weapon
            if (!player->hasWeapon(weapon->getName())) {
                if (player->addCoins(-weapon->getCost())){
                    player->giveWeapon(weapon);
                    has_bought_weapon = true;
                }
                else {
                    std::cout << "Can't afford this weapon!" << std::endl;
                }
            }
            else {
                std::cout << "Can't buy weapon, you already have this weapon." << std::endl;
            }
            break;
        
        default:
            break;
        }
    }
}

void Shop::render(sf::RenderWindow *win) {
    shop_list.render(win);
}