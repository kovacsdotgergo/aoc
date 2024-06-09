#include <iostream>
#include <regex>
#include <fstream>
#include <unordered_map>

int main(int argc, char* argv[]) {
    using std::cout, std::endl;
    std::unordered_map<std::string_view, int> 
        bag{{"red", 12}, {"green", 13}, {"blue", 14}};
    
    std::ifstream file{"inputs/input_day2"};
    if (!file) {
        cout << "couldn't open" << endl;
        return 1;
    }

    int sum = 0;
    std::string line;
    while (std::getline(file, line)) {
        // Finding the id
        std::regex id_pattern{"^Game (\\d+)"};
        std::smatch id_match;
        if (!std::regex_search(line, id_match, id_pattern)) {
            cout << "id not found" << endl;
            return 1;
        }
        auto id = atoi(id_match[1].str().c_str());

        // Extracting the picked values
        std::regex num_pattern{"(\\d+) (blue|red|green)"};
        auto it_begin = std::sregex_iterator(line.cbegin(), line.cend(), 
                                             num_pattern);
        auto it_end = std::sregex_iterator();
        bool possible = true;
        for (std::sregex_iterator it = it_begin; it != it_end; ++it) {
            // m[0] is always the whole match, the rest is the groups
            std::smatch m = *it;
            if (bag[m[2].str()] < atoi(m[1].str().c_str())) {
                possible = false;
                break;
            }
        }

        sum += possible ? id : 0;
    }

    cout << "sum: " << sum << endl;
    return 0;
}