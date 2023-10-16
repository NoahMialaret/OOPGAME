#include "Dialogue.h"


Dialogue::Dialogue() {

    if(!font.loadFromFile("files/dogicapixel.ttf")){
        std::cout << "Error Loading Font!" << std::endl;
    }

    // change the size to 100x100
    rectangle.setSize(sf::Vector2f(300, 100));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setOutlineColor(sf::Color::Yellow);
    rectangle.setOutlineThickness(4.0f);
    rectangle.setPosition(sf::Vector2f(275, 100));

    //std::cout << cur_line << std::endl;

    text.setCharacterSize(16); // in pixels, not points!
    text.setFillColor(sf::Color::White);

    text.setPosition(sf::Vector2f(300,150));
    
    
}

void Dialogue::startDialogue(std::string name){

    std::string filename = "files/NPCDialogues.txt"; // Set the filename
    text.setFont(font); // font is a sf::Font 
    
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

    // inside the main loop, between window.clear() and window.display()
    win->draw(rectangle);
    win->draw(text);
    
}



