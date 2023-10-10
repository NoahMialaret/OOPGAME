#include "Button.h"

Button::Button(Texture tex) {
    sprite.setTexture(tex);
    clicked = false;
}

bool Button::get_clicked() {
    return clicked;
}
void Button::set_clicked(bool clicked) {
    this->clicked = clicked;
}

bool Button::checkClicked() {
    
}