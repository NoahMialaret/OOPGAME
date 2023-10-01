#include "NPC.h"

NPC::NPC(const char *tex_name, float game_scale, sf::Vector2f pos, const char* name)
    :
    Entity(tex_name, game_scale, pos),
    name(name)
{}

void NPC::renderDialogue(sf::RenderWindow* win) {

    std::ifstream file("files/dialogue.txt");

    if (!file) {
        std::cout << "Could not open dialogue file (expecting 'files/dialogue.txt')" << std::endl;
        return;
    }

    std::string fileline;
    while (std::getline(file, fileline) && fileline != "[" + name + "]") {}

    if (fileline != "[" + name + "]") {
        std::cout << "Could not find dialogue for " << name << std::endl;
        return;
    }

    sf::Font font;

    font.loadFromFile("files/dogicapixel.ttf");

    std::getline(file, fileline);
    sf::Text text(fileline, font);

    text.setFillColor(sf::Color(255,255,255));
    text.setOrigin(sf::Vector2f(0.0f,0.0f));

    win->draw(text);
}

std::string NPC::getName() const {
    return name;
}
