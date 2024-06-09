#include <iostream>
#include <regex>
#include <fstream>
#include <unordered_map>
#include <numeric>

int main(int argc, char* argv[]) {
    using std::cout, std::endl;
    
    std::ifstream file{"inputs/input_day2"};
    if (!file) {
        cout << "couldn't open" << endl;
        return 1;
    }

    int power = 0;
    std::string line;
    std::unordered_map<std::string_view, int> 
        maxes{{"red", 0}, {"green", 0}, {"blue", 0}};
    std::regex num_pattern{"(\\d+) (blue|red|green)"};
    constexpr short unsigned kNumIndex = 1;
    constexpr short unsigned kColorIndex = 2;

    while (std::getline(file, line)) {
        // Extracting the picked values
        auto it_begin = std::sregex_iterator(line.cbegin(), line.cend(), 
                                             num_pattern);
        auto it_end = std::sregex_iterator();
        for (std::sregex_iterator it = it_begin; it != it_end; ++it) {
            // m[0] is always the whole match, the rest is the groups
            std::smatch m = *it;
            int& maxNum = maxes[m[kColorIndex].str()];
            int currentNum = atoi(m[1].str().c_str());
            
            maxNum = maxNum < currentNum ? currentNum : maxNum;
        }

        power += std::accumulate(maxes.cbegin(), maxes.cend(), 1,
                                 [](auto cum, auto right){return cum * right.second;});
        maxes = {{"red", 0}, {"green", 0}, {"blue", 0}};
    }

    cout << "sum power: " << power << endl;
    return 0;
}