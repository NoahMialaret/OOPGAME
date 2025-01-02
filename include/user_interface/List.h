#ifndef LIST_H
#define LIST_H

#include "SFML/Graphics.hpp"

#include <iostream>
#include <vector>

class List {
private:
    std::vector<std::string> list;
    sf::Font font;
    sf::Text text;
    sf::Vector2f list_position;
    sf::RectangleShape list_background_rect;

    // Determine which item in a list should be highlighted
    int highlight_index = -1;
public:
    List();
    void setText(float game_scale);                  // Sets the properties of sprites
    int update(sf::Vector2f mouse_pos);              // Uses the mouse position to determine which (if any) button in the list is being hovered over

    bool isListEmpty();                              // Returns whether or not the list has no elements in it
    void resetList();                                // Clears the content of the list
    void makeList(std::vector<std::string> new_list, 
        const sf::Vector2f new_position);            // Creates a new list of strings to be displayed
    void render(sf::RenderWindow* win);          // Renders the list and background rectangles
};

#endif