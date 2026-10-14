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
    template <typename ComponentType>
    constexpr EntityID componentTypeToIndex() {
        constexpr int temp = Pack<ComponentTypes...>::template index<ComponentType>;
        static_assert(temp != -1, "Component Type does not exist.");
        return static_cast<EntityID>(temp);
    }

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

    template <typename ComponentType> 
    bool hasComponent(EntityID id) const {
        constexpr EntityID typeIdx = componentTypeToIndex<ComponentType>();
        static_assert(validEntity(id));
        return mComponentIndicies[typeIdx][id] != INVALID_COMPONENT_INDEX;
    }

    template <typename ComponentType>
    ComponentType& getComponent(EntityI id) const {
        constexpr EntityID typeIdx = componentTypeToIndex<ComponentType>();
        assert(hasComponent<ComponentType>(id));
        auto& registry = std::get<typeIdx>(mRegistries);
        return registry[mComponentIndicies[typeIdx][id]];
    }

private:
    string name = "FirstEM";
    std::tuple<Registry<ComponentTypes>...> mRegistries;
    std::array<std::vector<EntityID>, sizeof...(ComponentTypes)> mComponentIndicies;
    std::vector<bool> mValid;
    std::vector<EntityID> mFreeList;

    static constexpr EntityID INVALID_COMPONENT_INDEX = std::numeric_limits<EntityID>::max();
};

#endif  // ENTITY_MANAGER_H
