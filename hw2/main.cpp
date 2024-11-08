#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>


int main() {
    std::vector<std::set<char>> words;
    std::string word;

    while (true) {
        std::getline(std::cin, word);
        if (word.empty()) {
            break;
        }
        std::set<char> letters(word.begin(), word.end());
        words.push_back(letters);
    }

    if (words.empty()) {
        std::cout << std::endl;
        return 0;
    }

    std::set<char> common_letters = words[0];

    for (size_t i = 1; i < words.size(); ++i) {
        std::set<char> temp;
        std::set_intersection(common_letters.begin(), common_letters.end(),
                              words[i].begin(), words[i].end(),
                              std::inserter(temp, temp.begin()));
        common_letters = temp;
    }

    for (char letter : common_letters) {
        std::cout << letter;
    }
    std::cout << std::endl;

    return 0;
}
