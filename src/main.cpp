#include <iostream>
#include "classes/Polyhedron.h"

int main() {
    Polyhedron A;
    std::vector<size_t> aaa = {1, 2, 3, 4};
    std::erase(aaa, 0);
    for (auto i: aaa) {
        std::cout << i;

    }
    std::cin >> A;
    std::cout << A;
    return 0;
}