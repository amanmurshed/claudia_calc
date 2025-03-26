#include "claudia_calc_example.h"
#include <sys/types.h>
#include <iostream>
#include "spdlog/spdlog.h"
using namespace std;

namespace claudia_calc {

/*
 * utility functions
 */

inline bool is_register(char const ch) { return tolower(ch) >= 'a' && ch <= 'd'; }

inline bool is_register(string const str) { return str.size() != 0 && is_register(str[0]); }

inline reg_name to_reg_name(char const ch) {
    assert(is_register(ch));
    return static_cast<reg_name>(tolower(ch) - 'a');
}

inline reg_name to_reg_name(string const str) {
    assert(is_register(str));
    return to_reg_name(str[0]);
}

inline char to_char(reg_name rn) { return static_cast<char>(rn + 'a'); }

/*
 * calculator functions
 */

inline void print_line() { cout << std::string(MENU_WIDTH, '-') << endl; }

inline void print_title(string const title) { cout << fmt::format("{:^{}}", title, MENU_WIDTH) << endl; }

// print the registers
void print_registers(Calculator& calc) {
    cout << "\t\tA number = " << calc.format_number(calc.registers[A]) << "\t\t";
    cout << "  B number = " << calc.format_number(calc.registers[B]) << "\t\t";
    cout << "  C number = " << calc.format_number(calc.registers[C]) << "\t\t";
    cout << "  D number = " << calc.format_number(calc.registers[D]) << endl;
}

void print_menu(Calculator& calc) {
    print_line();
    print_title("ClaudiaCalc");
    print_line();
    print_registers(calc);
    print_line();
    cout << "+\tAdd" << endl;
    cout << "-\tSubtract" << endl;
    cout << "*\tMultiply" << endl;
    cout << "/\tDivide" << endl;
    cout << "a-d\tEnter a number or string for A,B,C,D" << endl;
    cout << "1-4\tClear register A,B,C,D" << endl;
    cout << "m\tPrints the menu" << endl;
    cout << "p\tPrints the registers" << endl;
    cout << "q\tQuits the app" << endl;
    print_line();
}

void execute(string const cmd, Calculator& calc) {
    // validate command size
    if (cmd.size() == 0) {
        spdlog::error("Empty command");
        return;
    }
    // lower annd get first char of command
    char const cmd_ch = std::tolower(cmd[0]);

    switch (cmd_ch) {
        case 'a':
        case 'b':
        case 'c':
        case 'd': {
            cout << "Enter value for register " << cmd_ch << ": ";
            float value;
            // Check if input is a number
            if (cin >> value) {
                calc.registers[to_reg_name(cmd_ch)] = value;
                print_registers(calc);
            } else {
                spdlog::error("Invalid number entered");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        }
        case '+':
        case '-':
        case '*':
        case '/': {
            char lhs, rhs;
            cout << "Enter a lhs register: ";
            cin >> lhs;
            cout << "Enter a rhs register: ";
            cin >> rhs;

            // Validate lhs and rhs
            reg_name lhs_reg = to_reg_name(lhs);
            reg_name rhs_reg = to_reg_name(rhs);
            float result = 0.0f;

            switch (cmd_ch) {
                case '+':
                    result = calc.registers[lhs_reg] + calc.registers[rhs_reg];
                    break;
                case '-':
                    result = calc.registers[lhs_reg] - calc.registers[rhs_reg];
                    break;
                case '*':
                    result = calc.registers[lhs_reg] * calc.registers[rhs_reg];
                    break;
                case '/':
                    if (calc.registers[rhs_reg] == 0.0f) {
                        spdlog::error("{} / {} is invalid. Cannot divide by zero", lhs, rhs);
                        return;
                    }
                    result = calc.registers[lhs_reg] / calc.registers[rhs_reg];
                    break;
            }

            // Store result in A register
            calc.registers[A] = result;
            print_registers(calc);
            break;
        }
        case '1':
        case '2':
        case '3':
        case '4': {
            // Convert char to register
            reg_name reg = static_cast<reg_name>(cmd_ch - '1');
            calc.registers[reg] = 0.0f; // Clear register
            print_registers(calc);
            break;
        }
        case 'm':
            print_menu(calc);
            break;
        case 'p':
            print_registers(calc);
            break;
        case 'q':
            break;
        default:
            spdlog::error("{} is an unknown command", cmd_ch);
            break;

    }
}

// start the calculator
void start() {
    string cmd = "";
    Calculator calc;
    // print menu
    print_menu(calc);
    while (cmd != "q") {
        cout << "Enter a command: ";
        cin >> cmd;
        // spdlog::debug("cmd={}", cmd);
        execute(cmd, calc);
    }
}
}  // namespace claudia_calc

using namespace claudia_calc;

int main() {
    spdlog::set_level(spdlog::level::debug);
    start();

    return 0;
}
