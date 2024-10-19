#include <fstream>
#include <list>
#include <map>
#include <err.h>


std::vector<std::string> split_by_nletter(std::string &str) {
    std::vector<std::string> splitted_string;

    unsigned int elem_idx = 0;
    std::string elem = {};
    for (char i : str) {
        if ((i >= 'a' and i <= 'z') or (i >= 'A' and i <= 'Z') or (i >= '0' and i <= '9')) {
            elem.push_back(i);
        } else {
            if (!elem.empty()) { // current substring isn't empty
                splitted_string.push_back(elem);
                elem = {};
                ++elem_idx;
            }
        }
    }
    if (!elem.empty()) {splitted_string.push_back(elem); }

    return splitted_string;
}


bool cmp(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
    return a.second < b.second;
}


int main(int argc, char** argv) {
    if (argc != 3) {
        err(3, "");
    }

    std::ifstream in;
    std::ofstream out;

    in.open(argv[1]);
    out.open(argv[2]);

//    in.open("/Users/andrejalekseevic/study/oop/tsk0b/some_text.txt");
//    out.open("/Users/andrejalekseevic/study/oop/tsk0b/data.csv");

//    std::list<std::string> data;
    std::map<std::string, int> repetitions;
    std::string s;

    while (!in.eof()) {
        std::getline(in, s);

        for (std::string &i : split_by_nletter(s)) {
            if (repetitions.find(i) == repetitions.end()) {
                repetitions[i] = 1;
            } else {
                ++repetitions[i];
            }
        }
    }

    std::vector<std::pair<std::string, int>> data;
    data.reserve(repetitions.size());
    double words_count = 0;

    for (auto const &i: repetitions) {
            data.emplace_back(i);
            words_count += i.second;
        }

    std::sort(data.rbegin(), data.rend(), cmp);

    if (out.is_open()) {
        for (const std::pair<std::string, int> &line : data) {
            out << line.first << ',' << line.second << ',' << (line.second / words_count) << std::endl;
        }
    }
    out.close();

    return 0;
}
