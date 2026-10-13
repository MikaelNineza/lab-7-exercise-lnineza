#ifndef REGISTRY_H
#define REGISTRY_H

#include <vector>
#include <limits>
template <typename T>
class Registry {
public:
    size_t store(T&& t) {
        size_t id;
        if (!mFreeList.empty()) {
            id = mFreeList.back();
            mFreeList.pop_back();
            mData[id] = std::forward<T>(t);
            mValid[id] = true;
        }
        else {
            id = mData.size();
            mData.push_back(std::forward<T>(t));
            mValid.push_back(true);
        }

        ++mValidCount;
        return id;
    }

    void remove(size_t id) {
        assert(valid(id));

        mData[id] = T{};
        mValid[id] = false;
        mFreeList.push_back(id);
        --mValidCount;
    }

    T& operator[](size_t id) {
        assert(valid(id));
        return mData[id];
    }

    const T& operator[](size_t id) const {
        assert(valid(id));
        return mData[id];
    }

    bool valid(size_t id) {
        return mValid.size() > id && mValid[id];
    }

    size_t size() {
        return mValidCount;
    }

    void reserve(size_t capacity) {
        mData.reserve(capacity);
        mValid.reserve(capacity);
    }

private:
    std::vector<T> mData;
    std::vector<bool> mValid;
    std::vector<size_t> mFreeList;
    size_t mValidCount = 0;
};

#endif  // REGISTRY_H
