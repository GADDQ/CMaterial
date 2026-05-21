//
// Created by Earth_Studio on 2026/5/1.
//

#pragma once


#include <unordered_map>
#include <list>
#include <utility>


namespace cmaterial::utils {
    template<typename K, typename V>
    class ordered_map {
    public:
        using ValueType = std::pair<const K, V>;
        using ListIter = typename std::list<ValueType>::iterator;

        std::pair<ListIter, bool> insert(const K& key, V value) {
            auto it = lookup.find(key);
            if (it != lookup.end()) {
                return {it->second, false};
            }

            data.emplace_back(key, value);
            ListIter lastIt = std::prev(data.end());

            lookup[key] = lastIt;
            return {lastIt, true};
        }

        std::pair<ListIter, bool> insert(const ValueType& value) {
            return insert(value.first, value.second);
        }

        std::pair<ListIter, bool> insert(ValueType&& value) {
            auto it = lookup.find(value.first);
            if (it != lookup.end()) return {it->second, false};

            data.emplace_back(std::move(value));
            ListIter lastIt = std::prev(data.end());
            lookup[lastIt->first] = lastIt;
            return {lastIt, true};
        }

        V& operator[](const K& key) {
            auto it = lookup.find(key);
            if (it == lookup.end()) {
                return insert(key, V{}).first->second;
            }
            return it->second->second;
        }

        size_t erase(const K& key) {
            auto it = lookup.find(key);
            if (it == lookup.end()) return 0;

            data.erase(it->second);
            lookup.erase(it);
            return 1;
        }

        auto begin() noexcept { return data.begin(); }
        auto end()   noexcept { return data.end(); }
        auto begin() const noexcept { return data.begin(); }
        auto end()   const noexcept { return data.end(); }

        bool contains(const K& key) const { return lookup.contains(key); }
        bool empty() const noexcept { return lookup.empty(); }
        size_t size() const noexcept { return lookup.size(); }

        void clear() noexcept {
            lookup.clear();
            data.clear();
        }

        auto find(const K& key) {
            auto it = lookup.find(key);
            return (it == lookup.end()) ? data.end() : it->second;
        }

    private:
        std::list<ValueType> data;
        std::unordered_map<K, ListIter> lookup;
    };
}