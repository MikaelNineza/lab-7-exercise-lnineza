#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <cstddef>  // size_t
#include <limits>
#include <string>
#include <tuple>

#include "pack.h"  // Pack from prep
#include "registry.h"

using EntityID = size_t;

template <typename... ComponentTypes>
class EntityManager {
public:
    EntityID createEntity() {
        EntityID id;
        if (!mFreeList.empty()) {
            id = mFreeList.back();
            mFreeList.pop_back();
            mValid[id] = true;
        }
        else {
            id = mValid.size();
            for (auto& indicies : mComponentIndicies) {
                    indicies.push_back(INVALID_COMPONENT_INDEX);
            }
            mValid.push_back(true);
        }

        return id;
    }

    bool validEntity(EntityID id) const {
        return mValid.size() > id && mValid[id];
    }

    
private:
    string name = "FirstEM";
    std::tuple<std::vector<Registry<ComponentTypes>...> mRegistries;
    std::array<std::vector<EntityID>, sizeof...(ComponentTypes)> mComponentIndicies;
    std::vector<bool> mValid;
    std::vector<EntityID> mFreeList;

    static constexpr EntityID INVALID_COMPONENT_INDEX = std::numeric_limits<EntityID>::max();
};

#endif  // ENTITY_MANAGER_H
