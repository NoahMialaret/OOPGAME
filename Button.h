#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SFML/Graphics.hpp>
using namespace sf;

class Button {
    private:
        Sprite sprite;
        bool clicked;

    public:
        Button(Texture tex);

        bool get_clicked();
        void set_clicked(bool clicked);

        bool checkClicked();



};

#endif