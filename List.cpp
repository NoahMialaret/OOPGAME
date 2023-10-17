#include "List.h"

List::List() {
    if (!font.loadFromFile("files/dogicapixel.ttf")) {
        std::cout << "Could not load the font for List!" << std::endl;
    }
}

void List::setText(float game_scale) {

    text.setFont(font);
    text.setCharacterSize(32);
    list_background_rect.setSize(sf::Vector2f(0.0f, 40.0f));
    list_background_rect.setFillColor(sf::Color::Black);
}

void List::makeList(std::vector<std::string> new_list, const sf::Vector2f new_position) {
    list = new_list;

    float offset = 40.0f * list.size() - 4.0f;
    list_position = new_position + sf::Vector2f(0.0f, -offset);

    list_background_rect.setPosition(list_position.x, 0.0f);
}

int List::update(sf::Vector2f mouse_pos)
{    
    list_background_rect.setPosition(list_position.x, list_position.y - 4.0f);

    for (int i = 0; i < list.size(); i++) {
        list_background_rect.setSize(sf::Vector2f(list[i].size() * text.getCharacterSize(), list_background_rect.getSize().y));

        sf::FloatRect f_rect(list_background_rect.getPosition(), list_background_rect.getSize());
        if (f_rect.contains(mouse_pos.x, mouse_pos.y)) {
            highlight_index = i;
            return highlight_index;
        }

        list_background_rect.move(0.0f, 40.0f);
    }
    highlight_index = -1;

    return -1;
}

void List::render(sf::RenderWindow* win) {
    text.setPosition(list_position);
    list_background_rect.setPosition(list_background_rect.getPosition().x, text.getPosition().y - 4.0f);

    for (int i = 0; i < list.size(); i++) {
        if (i == highlight_index) {
            list_background_rect.setFillColor(sf::Color::White);
            text.setFillColor(sf::Color::Black);
        }
        else {
            list_background_rect.setFillColor(sf::Color::Black);
            text.setFillColor(sf::Color::White);
        }
        text.setString(list[i]);
        list_background_rect.setSize(sf::Vector2f(list[i].size() * text.getCharacterSize(), list_background_rect.getSize().y));
        win->draw(list_background_rect);
        win->draw(text);
        text.move(0.0f, 40.0f);
        list_background_rect.move(0.0f, 40.0f);
    }
}

bool List::isListEmpty() {
    return list.empty();
}

void List::resetList() {
    list.clear();
    list_position = sf::Vector2f(0.0f, 0.0f);
    highlight_index = -1;
}
