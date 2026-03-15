#include <bits/stdc++.h>
#include "TreeSS.h"

template <typename T>
struct MinOp {
    T operator()(const T &a, const T &b) const {
        return a < b ? a : b;
    }
};

template <typename T, typename Op>
inline TreeSS<T, Op>::TreeSS(const std::vector<T> &data, T identity, T lazyIdentity) : identity_(identity), lazyIdentity_(lazyIdentity)
{
    this->size = 1;
    while(this->size < data.size())
        this->size<<=1;
        
    this->data_.resize(this->size * 2, identity_);
    this->lazy.resize(this->size * 2, lazyIdentity_);

    for (size_t i = 0; i < data.size(); i++)
        this->data_[this->size + i] = data[i];


    for(size_t i = size-1; i > 0; i--)
        this->data_[i] = Op()(this->data_[2*i], this->data_[2*i+1]);

}

template <typename T, typename Op>
TreeSS<T, Op>::TreeSS(size_t size, T value, T identity, T lazyIdentity) : identity_(identity), lazyIdentity_(lazyIdentity)
{
    this->size = 1;
    while(this->size < size)
        this->size<<=1;
    
    this->data_.resize(this->size * 2, identity_);
    this->lazy.resize(this->size * 2, lazyIdentity_);

    for(size_t i = size; i < 2*size; i++)
        this->data_[i] = value;

    for(size_t i = size-1; i > 0; i--)
        this->data_[i] = Op()(this->data_[2*i], this->data_[2*i+1]);
}

template <typename T, typename Op>
void TreeSS<T, Op>::propagate(size_t l, size_t r, size_t pos)
{
    if (lazy[pos] != lazyIdentity_){
        size_t mid = (l + r) / 2;
        data_[pos * 2] += lazy[pos] * (mid - l + 1);
        data_[pos * 2 + 1] += lazy[pos] * (r - mid);
        lazy[pos * 2] += lazy[pos];
        lazy[pos * 2 + 1] += lazy[pos];
        lazy[pos] = 0;
    }
}

template <typename T, typename Op>
void TreeSS<T, Op>::update(size_t l, size_t r, T value, size_t cl, size_t cr, size_t pos)
{
    if (l > cr || r < cl)
        return;
    if (cl <= l && r <= cr){
        data_[pos] += value * (r - l + 1);
        lazy[pos] += value;
        return;
    }
    propagate(l, r, pos);
    size_t mid = (l + r) / 2;
    update(l, r, value, cl, mid, pos*2);
    update(l, r, value, mid+1, cr, pos*2+1);
    data_[pos] = Op()(data_[pos*2], data_[pos*2+1]);
}

template <typename T, typename Op>
T TreeSS<T, Op>::query(size_t l, size_t r, size_t cl, size_t cr, size_t pos)
{

    if (l > cr || r < cl)
        return identity_;
    if (cl <= l && r <= cr)
        return data_[pos];
    propagate(l,r,pos);
    size_t mid = (l + r) / 2;
    return Op()(query(l, r, cl, mid, pos*2), query(l,r, mid+1, cr, pos*2+1));

}

using namespace std;


int main(int argc, char *argv[])
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8};
    TreeSS<int, MinOp<int>> tree(a, 1e9, 0);
    
    cout << tree.query(1,2) << '\n';
    tree.update(2,2,6);
    cout << tree.query(2,4) << '\n';
    tree.update(1, 7, 20);
    cout << tree.query(3,6) << '\n';

}
