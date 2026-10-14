#include <iostream>
#include <cassert>
#include <array>

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

    // For entity manager
    EntityManager<bool, float, int> manager;

    EntityID e1 = manager.createEntity();
    EntityID e2 = manager.createEntity();
    assert(e1 == 0 && e2 == 1);
    assert(manager.validEntity(e1) && manager.validEntity(e2));
    assert(!manager.validEntity(23));
    assert(!manager.hasComponent<bool>(e1) && !manager.hasComponent<float>(e1) && !manager.hasComponent<int>(e1));

    manager.addComponent(e1, 5);
    assert(!manager.hasComponent<bool>(e1) && !manager.hasComponent<float>(e1) && manager.hasComponent<int>(e1));
    assert(manager.getComponent<int>(e1) == 5);

    float f = 23.08f;
    const bool b = false;
    manager.addComponent(e1, f);
    manager.addComponent(e1, b);

    
    return 0;
}
