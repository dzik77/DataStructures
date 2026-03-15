#include <bits/stdc++.h>

struct Max
{
    template<typename T>
    T operator()(const T &a, const T &b) const {
        return std::max(a, b);
    }
};
struct Min
{
    template<typename T>
    T operator()(const T &a, const T &b) const {
        return std::min(a, b);
    }
};

template<typename T = int, typename Op = std::plus<T>>
struct TreePS
{
    TreePS(const std::vector<T> &data, T identity) : identity_(identity){
        this->size = 1;
        while(this->size < data.size())
            this->size<<=1;
        this->data.resize(this->size * 2, identity_);
        for (size_t i = 0; i < data.size(); i++)
            this->data[this->size + i] = data[i];
        for(size_t i = size-1; i > 0; i--)
            this->data[i] = Op()(this->data[2*i], this->data[2*i+1]);
    }
    TreePS(size_t size, T value, T identity) : identity_(identity){
        this->size = 1;
        while(this->size < size)
            this->size<<=1;
        this->data.resize(this->size * 2, identity_);
        for(size_t i = size; i < 2*size; i++)
            this->data[i] = value;
        for(size_t i = size-1; i > 0; i--)
            this->data[i] = Op()(this->data[2*i], this->data[2*i+1]);
    }
    T query(size_t l, size_t r) const
    {
        size_t lpos = l + this->size, rpos = r + 1 + this->size;
        T res = identity_;
        while(lpos < rpos){
            if(lpos&1){
                res = Op()(res, this->data[lpos]);
                lpos++;
            }
            if(rpos&1){
                rpos--;
                res = Op()(res, this->data[rpos]);
            }
            lpos>>=1;
            rpos>>=1;
        }
        return res;
    }
    void update(size_t i, T value){
        size_t pos = i + this->size;
        this->data[pos] = value;
        pos >>= 1;
        while(pos > 0){
            this->data[pos] = Op()(this->data[2*pos], this->data[2*pos+1]);
            pos>>=1;
        }
    }
    size_t size;
    T identity_;
    std::vector<T> data;
};

template<typename T = int, typename Op = std::plus<T>>
class HevylightDecompositon{
public:
    int n, curpos, root;
    T identity;
    std::vector<std::vector<int>> const& graph;
    std::vector<T> parent, depth, heavy, head, pos;
    TreePS<T,Op> Tree;
    HevylightDecompositon(std::vector<std::vector<int>> const& graph, std::vector<T> array, T identity, int root)
        : n(graph.size()), 
          Tree(array.size(), identity, identity),
          identity(identity), root(root), graph(graph) {
        parent.resize(n,-1);
        depth.resize(n);
        heavy.resize(n,-1);
        head.resize(n);
        pos.resize(n);
        dfs(root);
        curpos = 0;
        decompose(root,root);
        std::vector<T> initarray(array.size());
        for (int i = 0; i < array.size(); i++){
            initarray[pos[i]] = array[i];
        }
        Tree = TreePS<T,Op>(initarray, identity);
    }
    int dfs(int v){
        int sz = 1;
        int maxsize = 0;
        for (auto u : graph[v]){
            if (u == parent[v]) continue;
            parent[u] = v; depth[u] = depth[v] + 1;
            size_t cursize = dfs(u);
            sz += cursize;
            if (cursize > maxsize){
                maxsize = cursize;
                heavy[v] = u;
            }
        }
        return sz;
    }
    void decompose(int v, int h){
        head[v] = h; pos[v] = curpos++;
        if (heavy[v] != -1){
            decompose(heavy[v], h);
        }
        for (auto u : graph[v]){
            if (u == heavy[v] || u == parent[v]) continue;
            decompose(u, u);
        }
    }
    T queryPath(int u, int v){
        T res = identity;
        while(head[u] != head[v]){
            if(depth[head[u]] > depth[head[v]])
                std::swap(u,v);
            res = Op()(res, Tree.query(pos[head[v]], pos[v]));
            v = parent[head[v]];
        }
        if (depth[u] > depth[v]) std::swap(u,v);
        res = Op()(res, Tree.query(pos[u], pos[v]));
        return res;
    }
    void updateNode(int u, T val){
        Tree.update(pos[u],val);
    }

};