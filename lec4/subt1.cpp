#include <iostream>
#include <tuple>


template <std::size_t idx, typename... Args>
void print_tuple(std::ostream& stream, const std::tuple<Args...>& t) {
    if constexpr (idx < sizeof...(Args)) {
        if (idx != 0) {
            stream << ", ";
        }
        stream << std::get<idx>(t);

        print_tuple<idx + 1>(stream, t);
    }
}


template <typename... Args>
auto operator<<(std::ostream& stream, const std::tuple<Args...>& t) -> std::ostream& {
    if constexpr (sizeof...(Args) == 0) {
        stream << "{}";
    } else {
        stream << "{";
        print_tuple<0>(stream, t);
        stream << "}";
    }

    return stream;
}

int main() {
    std::tuple<int, int, double, std::string, std::string, char> t = {2, 12, 2.2, "asdasda", "1", 's'};
    std::cout << t << std::endl;

    std::tuple<> tt = {};
    std::cout << tt << std::endl;

    return 0;
}
