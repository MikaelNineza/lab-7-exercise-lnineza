#include <iostream>
#include <cassert>

#include "entity_manager.h"

int main() {
    // test here...
    Registry<std::string> registry;

    std::string str1 = "Test1";
    size_t id1 = registry.store(str1);
    size_t id2 = registry.store(std::string("Test2"));
    assert(id1 == 0);
    assert(id2 == 1);
    assert(str1 == "Test1");
    assert(registry.size() == 2);

    return 0;
}
