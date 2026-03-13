#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll

struct LazySegTree{
 
    vector<ll> data, lazyAdd, lazyAssign;
    int n;
    LazySegTree(int size){
        n = size;
        int sz = 1;
        while(sz < size) sz <<= 1;
        data.assign(sz*2,0);
        lazyAdd.assign(sz*2,-1);
        lazyAssign.assign(sz*2,-1);
    }
    LazySegTree(vector<int>&arr){
        n = arr.size();
        int sz = 1;
        while(sz < arr.size()) sz <<= 1;
        data.assign(sz*2,0);
        lazyAdd.assign(sz*2,-1);
        lazyAssign.assign(sz*2,-1);
        build(1,0,n-1,arr);
    }
    void build(int x, int l, int r, vector<int> &arr){
        if (l == r){
            data[x] = arr[x];
            return;
        }
        int m = (l + r) / 2;
        build(x*2,l,m,arr);
        build(x*2+1,m+1,r,arr);
        data[x] = data[x*2] + data[x*2+1];
    }
    void apply(int x, int l, int r, int lAdd, int lAss){
        if (lAss != -1){
            data[x] = lAss * (r - l + 1);
            lazyAssign[x] = lAss;
            lazyAdd[x] = -1;
        }
        if (lAdd != -1){
            data[x] += lAdd * (r - l + 1);
            if (lazyAdd[x] == -1)
                lazyAdd[x] = lAdd;
            else
                lazyAdd[x] += lAdd;
        }
    }
    void push(int x, int l, int r){
        if (l == r || (lazyAdd[x] == -1 && lazyAssign[x] == -1)) return;
        int m = (l + r) / 2;
        apply(x*2,l,m,lazyAdd[x],lazyAssign[x]);
        apply(x*2+1,m+1,r,lazyAdd[x],lazyAssign[x]);
        lazyAdd[x] = -1;
        lazyAssign[x] = -1;
    }
    void update_add(int x, int l, int r, int ql, int qr, int val){
        if (r < ql || qr < l) return;
        if (ql <= l && r <= qr){
            apply(x,l,r,val,-1);
            return;
        }
        push(x,l,r);
        int m = (l + r) / 2;
        update_add(x*2,l,m,ql,qr,val);
        update_add(x*2+1,m+1,r,ql,qr,val);
        data[x] = data[x*2] + data[x*2+1];
    }
    void update_add(int ql, int qr, int val){
        update_add(1,0,n-1,ql,qr,val);
    }
    void update_assign(int x, int l, int r, int ql, int qr, int val){
        if (r < ql || qr < l) return;
        if (ql <= l && r <= qr){
            apply(x,l,r,-1,val);
            return;
        }
        push(x,l,r);
        int m = (l + r) / 2;
        update_assign(x*2,l,m,ql,qr,val);
        update_assign(x*2+1,m+1,r,ql,qr,val);
        data[x] = data[x*2] + data[x*2+1];
    }
    void update_assign(int ql, int qr, int val){
        update_assign(1,0,n-1,ql,qr,val);
    }
    int query(int x, int l, int r, int ql, int qr){
        if (r < ql || qr < l) return 0;
        if (ql <= l && r <= qr){
            return data[x];
        }
        push(x,l,r);
        int m = (l + r) / 2;
        return query(x*2,l,m,ql,qr) + query(x*2+1,m+1,r,ql,qr);
    }
    int query(int ql, int qr){
        return query(1,0,n-1,ql,qr);
    }
};