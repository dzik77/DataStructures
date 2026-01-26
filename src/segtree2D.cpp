#include <bits/stdc++.h>
using namespace std;

struct Segtree2D{
    int n,m;
    vector<vector<int>> data;
    vector<vector<int>> *arr=nullptr;
    Segtree2D(){}
    Segtree2D(int n,int m){

    }
    Segtree2D(vector<vector<int>> *a) : arr(a){
        n = (*arr).size(), m = (*arr)[0].size();
        data.resize(4*n,vector<int>(4*m));
        build_x(1,0,n-1);
    }
    void build_y(int vx, int lx, int rx, int vy, int ly, int ry){
        if (ly == ry){
            if (lx == rx){
                data[vx][vy] = (*arr)[lx][ly];
            }
            else{
                data[vx][vy] = data[vx*2][vy] + data[vx*2+1][vy];
            }
        }
        else{
            int my = (ly + ry) / 2;
            build_y(vx,lx,rx,vy*2,ly,my);
            build_y(vx,lx,rx,vy*2+1,my+1,ry);
            data[vx][vy] = data[vx][vy*2] + data[vx][vy*2+1];
        }
    }
    void build_x(int vx, int lx, int rx){
        if (lx != rx){
            int mx = (lx + rx) / 2;
            build_x(vx*2,lx,mx);
            build_x(vx*2+1,mx+1,rx);
        }
        build_y(vx,lx,rx,1,0,m-1);
    }
    int query(int lx, int rx, int ly, int ry){
        return query_x(1,0,n-1,lx,rx,ly,ry);
    }
    int query_y(int vx, int vy, int ly, int ry, int qly, int qry){
        if (qly > qry) return 0;
        if (ly == qly && ry == qry)
            return data[vx][vy];
        int my = (ly + ry) / 2;
        return
            query_y(vx,vy*2,ly,my,qly,min(qry,my)) +
            query_y(vx,vy*2+1,my+1,ry,max(qly,my+1),qry);
    }
    int query_x(int vx, int lx, int rx, int qlx, int qrx, int qly, int qry){
        if (qlx > qrx) return 0;
        if (lx == qlx && rx == qrx){
            return query_y(vx, 1, 0, m-1, qly, qry);
        }
        int mx = (lx + rx) / 2;
        return
            query_x(vx*2,lx,mx,qlx,min(mx,qrx),qly,qry) +
            query_x(vx*2+1,mx+1,rx,max(qlx,mx+1),qrx,qly,qry);
    }
    void update(int x, int y, int val){
        update_x(1,0,n-1,x,y,val);
    }
    void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int qy, int val){
        if (ly == ry){
            if (lx == rx)
                data[vx][vy] = val;
            else
                data[vx][vy] = data[vx*2][vy] + data[vx*2+1][vy];
        } else {
            int my = (ly + ry) / 2;
            if (qy <= my)
                update_y(vx,lx,rx,vy*2,ly,my,qy,val);
            else
                update_y(vx,lx,rx,vy*2+1,my+1,ry,qy,val);
            data[vx][vy] = data[vx][vy*2] + data[vx][vy*2+1];
        }
    }
    void update_x(int vx, int lx, int rx, int qx, int qy, int val){
        if (lx != rx){
            int mx = (lx + rx) / 2;
            if (qx <= mx)
                update_x(vx*2,lx,mx,qx,qy,val);
            else
                update_x(vx*2+1,mx+1,rx,qx,qy,val);
        }
        update_y(vx,lx,rx,1,0,m-1,qy,val);
    }
};