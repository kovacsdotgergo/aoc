#include <fstream>
#include <iostream>
#include <sstream>


int main() {
    std::ifstream inputs_file{"inputs/input_day1"};
    if (!inputs_file) {
        std::cout << "couldn't open" << std::endl;
        return 1;
    }

    std::string line;
    const char* digits = "0123456789";
    unsigned int sum = 0;

    while(std::getline(inputs_file, line)) {
        const auto first_pos = line.find_first_of(digits);
        if (std::string::npos == first_pos) {
            std::cout << "first digit not found" << std::endl;
            return 1;
        }
        
        const auto last_pos = line.find_last_of(digits);

        sum += (line[first_pos] - '0') * 10 + (line[last_pos] - '0');
    }
    
    inputs_file.close();
    std::cout << "sum: " << sum << std::endl;
    return 0;
}