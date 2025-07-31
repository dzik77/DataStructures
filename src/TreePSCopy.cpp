#include <vector>
#include <functional>

struct Max
{
    template<typename T>
    T operator()(const T &a, const T &b) const {
        return max(a, b);
    }
};
struct Min
{
    template<typename T>
    T operator()(const T &a, const T &b) const {
        return min(a, b);
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