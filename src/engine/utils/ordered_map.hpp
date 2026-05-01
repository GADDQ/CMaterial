//
// Created by Earth_Studio on 2026/5/1.
//

#ifndef CMATERIAL_ORDERED_MAP_H
#define CMATERIAL_ORDERED_MAP_H



#include <unordered_map>
#include <list>
#include <string>
#include <utility>

namespace cmaterial::utils {
    template<typename K, typename V>
    class ordered_map {
    public:
        // 为了支持 for(auto& [k, v] : map)，必须定义这个内部类型
        using ValueType = std::pair<const K, V>;
        using ListIter = typename std::list<ValueType>::iterator;

        // 1. 插入：保持顺序，$O(1)$
        std::pair<ListIter, bool> insert(const K& key, V value) {
            auto it = lookup.find(key);
            if (it != lookup.end()) {
                return {it->second, false}; // 已存在，不覆盖
            }

            // 插入链表末尾，保证遍历顺序
            data.emplace_back(key, value);
            ListIter lastIt = std::prev(data.end());

            // 存入哈希表实现 O(1) 索引
            lookup[key] = lastIt;
            return {lastIt, true};
        }

        // 🔮 新增：接受 std::pair 的重载
        std::pair<ListIter, bool> insert(const ValueType& value) {
            return insert(value.first, value.second);
        }

        // 🔮 进阶：接受右值引用的重载（支持 move，更体面）
        std::pair<ListIter, bool> insert(ValueType&& value) {
            auto it = lookup.find(value.first);
            if (it != lookup.end()) return {it->second, false};

            data.emplace_back(std::move(value));
            ListIter lastIt = std::prev(data.end());
            lookup[lastIt->first] = lastIt;
            return {lastIt, true};
        }

        // 2. 下标操作：最顺手的语法
        V& operator[](const K& key) {
            auto it = lookup.find(key);
            if (it == lookup.end()) {
                return insert(key, V{}).first->second;
            }
            return it->second->second;
        }

        // 3. 删除：真正的 $O(1)$ 且维持链表完整性
        size_t erase(const K& key) {
            auto it = lookup.find(key);
            if (it == lookup.end()) return 0;

            data.erase(it->second); // $O(1)$ 从链表移除
            lookup.erase(it);       // $O(1)$ 从哈希表移除
            return 1;
        }

        // 4. 迭代器：让 for(auto& [k, v] : map) 绝对有序
        auto begin() noexcept { return data.begin(); }
        auto end()   noexcept { return data.end(); }
        auto begin() const noexcept { return data.begin(); }
        auto end()   const noexcept { return data.end(); }

        // 5. C++20 风格接口
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
        // 物理存储：链表负责“序”
        std::list<ValueType> data;
        // 逻辑索引：哈希表负责“速”
        std::unordered_map<K, ListIter> lookup;
    };
}



#endif //CMATERIAL_ORDERED_MAP_H
