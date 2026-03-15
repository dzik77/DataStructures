#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Line{
    ll a,b;
    Line(ll a, ll b) : a(a), b(b) {}
    ll get(int x){
        return a*x + b;
    }
};
struct LiChaoTree{

    vector<Line> tree;
    int X;
    LiChaoTree(int X) : X(X) {
        tree.assign(4*X+1,Line(0,2e18));
    }
    void insert(int x, int l, int r, Line new_line){
        int m = (l + r) / 2;
        bool left_better = new_line.get(l) < tree[x].get(l);
        bool middle_better = new_line.get(m) < tree[x].get(m);
        if (middle_better){
            swap(tree[x], new_line);
        }
        if (l == r) return;
        if (left_better != middle_better){
            insert(x*2, l, m, new_line);
        } else {
            insert(x*2+1, m+1, r, new_line);
        }
    }
    ll query(int x, int l, int r, int val){
        ll res = tree[x].get(val);
        if (l == r) return res;
        int mid = (l + r) / 2;
        if (val <= mid){
            return min(res, query(x*2, l, mid, val));
        } else {
            return min(res, query(x*2+1, mid+1,r,val));
        }
    }
    void insert(Line new_line){
        insert(1, 0, X, new_line);
    }
    ll query(int val){
        return query(1, 0, X, val);
    }

};