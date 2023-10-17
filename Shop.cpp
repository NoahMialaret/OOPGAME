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

    std::vector<std::string> shop_strings;

    std::string cost = intToString(weapon->getCost());

    shop_strings.push_back({weapon->getName() + " - " + cost});

    shop_strings.push_back("Arrow - 5 Coins");
    shop_strings.push_back("Heart - 20 Coins");

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

void Shop::update(sf::Vector2f mouse_pos, Dialogue* dialogue, bool* dialogue_active, bool is_left_mouse_pressed, bool is_right_mouse_pressed) {
    
    int index = shop_list.update(mouse_pos);

    if (is_left_mouse_pressed) {
        switch (index)
        {
        case 0: // Weapon
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
        case 1: // Arrow
            std::cout << "Buying an arrow..." << std::endl;
            if(player->addCoins(-5)) {
                if (!player->addArrows(1)) {
                    std::cout << "You have the max amount of arrows (10), giving coins back." << std::endl;
                    dialogue->startDialogue("MaxArrowError", sf::Vector2f(0.0f, 0.0f));
                    *dialogue_active = true;
                    player->addCoins(5);
                }
            }
            else {
                std::cout << "Not enough coins for arrows, need at least 5 coins!" << std::endl;
                dialogue->startDialogue("lackOfFunds", sf::Vector2f(0.0f, 0.0f));
                *dialogue_active = true;
            }
            break;

        case 2:
            std::cout << "Buying a Heart..." << std::endl;
            if(player->addCoins(-20)) {
                if (player->heal()) {
                    std::cout << "You are already at max health!" << std::endl;
                    dialogue->startDialogue("MaxHealthError", sf::Vector2f(0.0f, 0.0f));
                    *dialogue_active = true;
                    player->addCoins(20);
                }
            }
            else {
                std::cout << "Not enough coins for a heart, need at least 20 coins!" << std::endl;
                dialogue->startDialogue("lackOfFunds", sf::Vector2f(0.0f, 0.0f));
                *dialogue_active = true;
            }
            break;
        
        default:
            break;
        }
    }
    else if (is_right_mouse_pressed) {
        switch (index)
        {
        case 0: // Weapon
            dialogue->startDialogue(weapon->getName(), sf::Vector2f(0.0f, 0.0f));
            *dialogue_active = true;
            break;
        case 1: // arrows
            dialogue->startDialogue("Arrow", sf::Vector2f(0.0f, 0.0f));
            *dialogue_active = true;
            break;
        case 2: // health
            dialogue->startDialogue("Heart", sf::Vector2f(0.0f, 0.0f));
            *dialogue_active = true;
            break;
        
        default:
            break;
        }
    }
}

void Shop::render(sf::RenderWindow *win) {
    shop_list.render(win);
}