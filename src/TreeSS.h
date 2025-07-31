#pragma once
#include <vector>
#include <functional>

template<typename T = int, typename Op = std::plus<T>>
class TreeSS
{

    public:

        TreeSS(const std::vector<T> &data, T identity, T lazyIdentity);
        TreeSS(size_t size, T value, T identity, T lazyIdentity);
        //TreePS(const TreePS &other);
        //TreePS(TreePS &&other);
        //TreePS &operator=(const TreePS &other);
        //TreePS &operator=(TreePS &&other);

        T query(size_t l, size_t r) {
            return query(l, r, 0, size-1, 1);
        }
        void update(size_t l, size_t r, T value){
            update(l, r, value, 0, size-1, 1);
        }

    //private:

        void propagate(size_t l, size_t r, size_t pos);
        void update(size_t l, size_t r, T value, size_t cl, size_t cr, size_t pos);
        T query(size_t l, size_t r, size_t cl, size_t cr, size_t pos);

        size_t size;
        T identity_;
        T lazyIdentity_;
        std::vector<T> data_;
        std::vector<T> lazy;

};
