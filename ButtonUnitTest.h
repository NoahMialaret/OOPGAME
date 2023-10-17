#ifndef _BUTTON_UNIT_TEST_H_

#define _BUTTON_UNIT_TEST_H_

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>

using namespace sf;
using namespace std;

class ButtonUnitTest {
    public:
        RenderWindow* test_window;
        Button* test_button;
        Texture button_tex;

        bool runNewTest;
        bool testClicked;

        ButtonUnitTest() {
            if (!button_tex.loadFromFile("art/whiteImageForTesting.png",IntRect(0,0,50,50))) {
                cout << "Test button texture couldn't load" << endl;
            }

            test_window = new RenderWindow(sf::VideoMode(800, 600), "Button Unit Test", sf::Style::Close);
            test_button = new Button(&button_tex,100,100);

            runNewTest = false;
            testClicked = true;
        }

        void runTest() {
            while (test_window->isOpen()) {
                Event event;
                while (test_window->pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        test_window->close();
                    }

                    if (event.type == Event::MouseButtonReleased) {
                        runNewTest = true;
                    }
                }

                if (runNewTest) {
                    bool button_clicked = test_button->checkClicked(Mouse::getPosition(*test_window));

                    if (testClicked) {
                        if (button_clicked) {
                            cout << "Button click detected, UNEXPECTED" << endl;
                        } else if (!button_clicked) {
                            cout << "Button click not detected, EXPECTED" << endl;
                        }

                        cout << "\nNow, click the button" << endl;

                        testClicked = false;
                        runNewTest = false;

                    } else if (!testClicked) {
                        if (button_clicked) {
                            cout << "Button click detected, EXPECTED" << endl;
                        } else if (!button_clicked) {
                            cout << "Button click not detected, UNEXPECTED" << endl;
                        }

                        cout << "\nNow, click away from the button" << endl;

                        testClicked = true;
                        runNewTest = false;
                    }
                }

                test_window->clear();

                test_button->draw(test_window);

                test_window->display();
            }
        }
        
};

#endif