#include <bits/stdc++.h>


template<typename T = int, typename Op = std::plus<T>>
struct Node{
    std::shared_ptr<Node> left,right;
    T value;
    Node(T val) : value(val), left(nullptr), right(nullptr) {}
    Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r) : left(l), right(r) {
        value = Op()(l->value, r->value);
    }
};

template<typename T = int, typename Op = std::plus<T>>
class PersistentSegmentTree {
public:
    std::vector<std::shared_ptr<Node<T, Op>>> roots;
    T identity_;
    size_t size;
    PersistentSegmentTree(const std::vector<T> &data, T identity) : size(data.size()), identity_(identity) {
        roots.push_back(build(0, data.size() - 1, data));
    }
    T query(size_t version, size_t l, size_t r) {
        assert(version < roots.size() && l <= r && r < size && l >= 0);
        return query_util(roots[version], 0, size - 1, l, r);
    }
    void update(size_t version, size_t idx, T value){
        assert(version < roots.size() && idx < size);
        roots.push_back(update_util(roots[version], 0, size - 1, idx, value));
    }

private:
    std::shared_ptr<Node<T,Op>> build(size_t l, size_t r, const std::vector<T> &data) {
        if (l == r){
            return std::make_shared<Node<T, Op>>(data[l]);
        }
        size_t mid = (l + r) >> 1;
        return std::make_shared<Node<T, Op>>(
            build(l, mid, data),
            build(mid + 1, r, data)
        );
    }
    T query_util(const shared_ptr<Node<T,Op>>& node, size_t l, size_t r, size_t ql, size_t qr){
        if (ql > qr){
            return identity_;
        }
        if (l == ql && r == qr){
            return node->value;
        }
        size_t mid = (l + r) >> 1;
        return Op()(
            query_util(node->left, l, mid, ql, std::min(qr, mid)),
            query_util(node->right, mid + 1, r, std::max(ql, mid + 1), qr)
        );
    }
    std::shared_ptr<Node<T, Op>> update_util(const std::shared_ptr<Node<T, Op>>& node, size_t l, size_t r, size_t idx, T value) {
        if (l == r) {
            return std::make_shared<Node<T, Op>>(value);
        }
        size_t mid = (l + r) >> 1; 
        if (idx <= mid){
            return std::make_shared<Node<T, Op>>(
                update_util(node->left, l, mid, idx, value),
                node->right
            );
        } else {
            return std::make_shared<Node<T, Op>>(
                node->left,
                update_util(node->right, mid + 1, r, idx, value)
            );
        }   
    }
};