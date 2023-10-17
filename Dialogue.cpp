#include "Dialogue.h"


Dialogue::Dialogue() {

    if(!font.loadFromFile("files/dogicapixel.ttf")){
        std::cout << "Error Loading Font!" << std::endl;
    }

    // change the size to 100x100
    rectangle.setSize(sf::Vector2f(600, 100));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setOutlineColor(sf::Color::Yellow);
    rectangle.setOutlineThickness(4.0f);

    //std::cout << cur_line << std::endl;

    text.setCharacterSize(16); // in pixels, not points!
    text.setFillColor(sf::Color::White);
 
}

void Dialogue::startDialogue(std::string name, sf::Vector2f screen_top_left){
    rectangle.setPosition(sf::Vector2f(125, 50) + screen_top_left);
    text.setPosition(sf::Vector2f(135, 110) + screen_top_left);   

    std::string filename = "files/dialogue.txt"; // Set the filename
    text.setFont(font); 
    
    if (file.is_open()) {
        file.close();
    }

    // Open the file
    file.open(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
    }

    std::cout << "Dialogue is starting!" << std::endl;
    
    while(getline(file, cur_line)){
        if(cur_line == name){
            break;
        }
    }

    getline(file, cur_line);

    text.setString(cur_line);

    std::cout << cur_line << std::endl;

}
bool Dialogue::readLine(){
    
    getline(file, cur_line);

    text.setString(cur_line);

    if(cur_line.size() == 0){
        return 1;
    }

    return 0;
}

void Dialogue::render(sf::RenderWindow* win) {
    win->draw(rectangle);
    win->draw(text);
}



