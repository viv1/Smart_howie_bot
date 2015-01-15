//
// Program Name: chatterbot1
// Description: this is a very basic example of a chatterbot program
//
// Author: Gonzales Cenelia
//

#include <iostream>
#include <string>
#include <ctime>

int main()
{
    std::string Response[] = {
        "I HEARD YOU!",
        "SO, YOU ARE TALKING TO ME.",
        "CONTINUE, I’M LISTENING.",
        "VERY INTERESTING CONVERSATION.",
        "TELL ME MORE..."
    };

    srand((unsigned) time(NULL));

    std::string sInput = "";
    std::string sResponse = "";

    while(1) {
        std::cout << ">";
        std::getline(std::cin, sInput);
        int nSelection = rand() % 5;
        sResponse = Response[nSelection];
        std::cout << sResponse << std::endl;
    }

    return 0;
}
