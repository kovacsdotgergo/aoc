#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <unordered_map>

int main() {
    std::unordered_map<std::string_view, short int> digit_to_value{
        {"nine", 9}, {"eight", 8}, {"seven", 7}, {"six", 6}, {"five", 5},
        {"four", 4}, {"three", 3}, {"two", 2}, {"one", 1},
        {"enin", 9}, {"thgie", 8}, {"neves", 7}, {"xis", 6}, {"evif", 5},
        {"ruof", 4}, {"eerht", 3}, {"owt", 2}, {"eno", 1},
        {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6},
        {"7", 7}, {"8", 8}, {"9", 9}};

    std::ifstream inputs_file{"inputs/input_day1"};
    if (!inputs_file) {
        std::cout << "couldn't open" << std::endl;
        return 1;
    }

    std::string line;
    std::regex digits{"[0-9]|one|two|three|four|five|six|seven|eight|nine"};
    std::regex reversed_digits{"\\d|eno|owt|eerht|ruof|evif|xis|neves|thgie|enin"};
    unsigned int sum = 0;

    while(std::getline(inputs_file, line)) {
        std::smatch digit_match;
        if (!std::regex_search(line, digit_match, digits)) {
            std::cout << "first digit not found" << std::endl;
            return 1;
        }

        std::match_results<decltype(line.crbegin())> reverse_digit_match;
        if (!std::regex_search(line.crbegin(), line.crend(),
                reverse_digit_match, reversed_digits)) {
            std::cout << "found num from left but not from right(shouldn't get here)" << std::endl;
            return 1;
        }
        
        sum += 10 * digit_to_value[digit_match[0].str()] 
            + digit_to_value[reverse_digit_match[0].str()];
    }
    
    inputs_file.close();
    std::cout << "sum: " << sum << std::endl;
    return 0;
}