#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SFML/Graphics.hpp>
using namespace sf;

class Button {
    private:
        Sprite sprite;
        bool clicked;

        int corner_x;
        int corner_y;

        //int width;
        //int length;

    public:
        Button(Texture* tex, int corner_x, int corner_y);

        bool get_clicked();
        void set_clicked(bool clicked);

        bool checkClicked(Vector2i position);

        int getSpriteWidth();
        int getSpriteHeight();

        void draw(RenderWindow* win);

};

#endif