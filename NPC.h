#ifndef NPC_H
#define NPC_H

#include "Entity.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "SFML/Graphics.hpp"

class NPC : public Entity {
private:
    std::string name;

public:
    NPC(const char* tex_name, float game_scale, sf::Vector2f pos, const char* name);
    void renderDialogue(sf::RenderWindow* win); // Temp until dialgue class is added
    std::string getName() const;
};

#endif