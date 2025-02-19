// The main function of the tetris game

// #include <iostream>
#include "headers\tetris.hpp"

int main()
{
    Tetris tetris = Tetris();
    setConsoleColor(0, tetris.piece[0].getBgColor());
    setCursorPosition(20, 10);
    std::cout << tetris.piece[0].type << std::endl;
    Sleep(1000);
    setConsoleColor(0, 0);
    tetris.run();
    return 0;
}