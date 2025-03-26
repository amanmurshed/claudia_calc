#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

#define NUM_REGISTERS 4
#define MENU_WIDTH 130

namespace claudia_calc {

enum reg_name { A = 0, B, C, D };
enum operation : char { PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVIDE = '/' };

/*
 * STUDENTS CAN DEFINE ANY DATA STRUCTURES OR DEFINTIONS THEY MAY NEED HERE
 */

 struct Calculator {
     float registers[NUM_REGISTERS] = {0.0f, 0.0f, 0.0f, 0.0f};

     // Format the number to 3 significant digits
     string format_number(float number) {
         stringstream ss;
         ss << fixed << setprecision(3) << number;
         return ss.str();
     }
 };

}  // namespace claudia_calc
