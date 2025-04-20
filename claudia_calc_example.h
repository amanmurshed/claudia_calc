#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <variant>

using namespace std;

#define NUM_REGISTERS 4
#define MENU_WIDTH 130

namespace claudia_calc {

enum reg_name { A = 0, B, C, D };
enum operation : char { PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/' };

// Define a register value type that can hold either float or string
using reg_value = std::variant<float, std::string>;

struct Calculator {
    reg_value registers[NUM_REGISTERS] = {0.0f, 0.0f, 0.0f, 0.0f};

    // Format the number to 3 significant digits
    string format_number(float number) {
        stringstream ss;
        ss << fixed << setprecision(3) << number;
        return ss.str();
    }
};

}  // namespace claudia_calc
