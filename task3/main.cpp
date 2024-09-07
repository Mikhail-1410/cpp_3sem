#include <iostream>
#include "my_math.hpp"

int main() {
    double angle;
    std::cin >> angle;
    
    AnswerHandler result = my_sin(angle);
    
    std::cout << "sin(" << result.x << ") = " << result.result << std::endl;
    
    return 0;
}
