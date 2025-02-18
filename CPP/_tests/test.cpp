#include <iostream>
#include <conio.h>

using namespace std;
int main()
{
    std::cout << "Hello, World!" << std::endl;
    // Read a number from the user
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;
    // Print the number to the console
    std::cout << "You entered: " << number << std::endl;

    // Read ANY key from the user to close the console
    std::cout << std::endl
              << "Press any key to close the console...";

    // Clear the input buffer
    std::cin.ignore();

    // Wait for the user to press a key
    _getch();
    return 0;
}