#include "my_math.hpp"

AnswerHandler my_sin(double x) {
    AnswerHandler result;
    result.x = x;

    double term = x;
    result.result = term;
    double x_squared = x * x;
    int n = 1; 

    for (int i = 1; i < 10; ++i) {
        term *= -x_squared / ((2 * n) * (2 * n + 1)); 
        result.result += term;
        ++n;
    }

    return result;
}
