/***********************************main.cpp*************************************************/
#include "Joc.h"

#include <stdexcept>
#include <iostream>

int main() {

    try {
        Joc joc;
        return joc.play();
    }
    catch (std::exception& e) {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }


}
