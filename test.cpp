#include<iostream>
#include<string>
#include<fstream>


int main(){
    std::fstream file("Dialogue.txt", std::ios::in);
    std::string line;

    if (file.is_open()){
        getline(file, line, '/n');

        std::cout << line << std::endl;
        file.close();
    }
}




std::string Dialogue::searchWord(name){
int main(void)
{
    std::string search;
    int offset;
    std::string line;

    std::ifstream Myfile;
    Myfile.open("1.txt");
    std::cout << "Enter the word to search: ";
    std::cin >> search;
    if (Myfile.is_open())
    {
        while (!Myfile.eof())
        {
            std::getline(Myfile, line);
            if ((offset = line.find(search, 0)) != string::npos)
            {
                cout << "The word has been found " << search << endl;
            }
        }
        Myfile.close();
    }
    else
        cout << "File opening error" << endl;
    system("pause");
    return 0;
}


loadFromFile("dogicapixel.ttf")