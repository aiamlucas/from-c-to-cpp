#include <iostream>
#include <string>

int main(void) {
    std::string brain = "HI THIS IS BRAIN";
    std::string *stringPTR = &brain;
    std::string &stringREF = brain;

    std::cout << &brain << std::endl;     // adress of brain
    std::cout << stringPTR << std::endl;  // adress stored in stringPTR
    std::cout << &stringREF << std::endl; // adress of what stringREF refers to
    std::cout << brain << std::endl;      // value of brain
    std::cout << *stringPTR << std::endl; // value pointed to by stringPTR
    std::cout << stringREF << std::endl;  // value of stringREF

    return 0;
}
