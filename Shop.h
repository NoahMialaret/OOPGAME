#ifndef SHOP_H
#define SHOP_H

#include "Weapon.h"
#include "Dialogue.h"
#include "Bow.h"
#include "BasicBow.h"
#include "List.h"
#include "MultiBow.h"
#include "CrossBow.h"
#include "BroardSword.h"
#include "Daggers.h"
#include "ShortSword.h"
#include "Player.h"

#include <SFML/Graphics.hpp>

#include <random>
#include <string>

class Shop {
private:
    Weapon* weapon = nullptr;
    List shop_list;

    bool has_bought_weapon = false;

    Player* player = nullptr;

public:
    Shop(std::mt19937 &rng, Player* player, int* player_arrows, float game_scale);
    ~Shop();
    std::string intToString(int number);    
    void update(sf::Vector2f mouse_pos, Dialogue* dialogue, bool* dialogue_active, bool is_left_mouse_pressed, bool is_right_mouse_pressed);
    void render(sf::RenderWindow* win);

    Weapon* getWeapon();
};

#endif