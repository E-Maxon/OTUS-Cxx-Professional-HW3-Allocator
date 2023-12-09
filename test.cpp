#include "container.h"
#include <iostream>

int main() {
    container<int> v;
    v.add(1);
    for (auto it = v.begin(); it != v.end(); it++) {
        std::cout << *it;
    }
}