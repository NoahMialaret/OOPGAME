#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const float PI = 3.14159265359;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Roulette Wheel");

    // Create the roulette wheel shape
    sf::CircleShape rouletteWheel(300);
    rouletteWheel.setFillColor(sf::Color::Black);
    rouletteWheel.setOutlineColor(sf::Color::Red);
    rouletteWheel.setOutlineThickness(5);
    rouletteWheel.setPosition(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 - 300);

    // Create the ball shape
    sf::CircleShape ball(20);
    ball.setFillColor(sf::Color::Red);

    // Define the initial angle for the ball
    float ballAngle = 0.0f;
    int randNum = 0;
    float ball_angle_change = randNum / 100;
    float ballX, ballY;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {

            case sf::Event::KeyPressed: {
                std::cout << "A key was pressed" << std::endl;
                randNum = rand() % 10 + 1;
                break;
            }

            case sf::Event::Closed: {
                window.close();
                break;
            }
            }
        }

        // Update the ball's position based on its angle
        ballX = WINDOW_WIDTH / 2 + 300 * std::cos(ballAngle);
        ballY = WINDOW_HEIGHT / 2 + 300 * std::sin(ballAngle);
        ball.setPosition(ballX - 20, ballY - 20);

        // Rotate the ball around the center of the wheel
        ballAngle += 0.01 * randNum ;

        randNum -= 0.001;

        if (ballAngle >= 2 * PI) {
            // Reset the angle when it completes one full rotation
            ballAngle = 0.0;
        }

        window.clear();
        window.draw(rouletteWheel);
        window.draw(ball);
        window.display();
    }

    return 0;
}