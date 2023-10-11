#include "Button.h"

Button::Button(Texture* tex, int corner_x, int corner_y, int width, int length) {
    sprite.setTexture(*tex);
    clicked = false;

    this->corner_x = corner_x;
    this->corner_y = corner_y;
    this->width = width;
    this->length = length;

    sprite.setPosition(corner_x, corner_y);
}

bool Button::get_clicked() {
    return clicked;
}
void Button::set_clicked(bool clicked) {
    this->clicked = clicked;
}

bool Button::checkClicked(Vector2i position) {
    if ((position.x >= corner_x && position.x <= (corner_x + width)) && 
    ((position.y >= corner_y && position.y <= (corner_y + length)))) {
        return true;
    }

    return false;
}

void Button::draw(RenderWindow* win) {
    win->draw(sprite);
}