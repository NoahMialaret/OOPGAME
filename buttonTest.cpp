#include "ButtonUnitTest.h"

int main() {
    ButtonUnitTest test;

    test.runTest();

    return 0;
}

//compile unit test with command: 
//g++ buttonTest.cpp Button.cpp -o buttonUnitTest -lsfml-graphics -lsfml-window -lsfml-system

//run with:
// ./buttonUnitTest