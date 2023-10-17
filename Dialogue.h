#ifndef _DIALOGUE_
#define _DIALOGUE_

#include "SFML/Graphics.hpp"

#include<string>
#include<iostream>
#include<random>
#include<fstream>

class Dialogue {
    private:
        std::string cur_line;
        sf::Font font;
        std::ifstream file;
        sf::Text text;
        sf::RectangleShape rectangle;
    public:
        Dialogue();
        void startDialogue(std::string name);
        bool readLine();
        void render(sf::RenderWindow* win);
        std::string get_cur_line();
        void set_set_line();
};

#endif