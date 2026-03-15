#include <bits/stdc++.h>
using namespace std;

const int K = 26;
struct Vertex{
    int next[K], go[K], link = 0;
    bool output = false;
    Vertex() {
        fill(next,next+K,-1);
        fill(go,go+K,-1);
    }
};
struct AhoCorasick{

    vector<Vertex> t;
    AhoCorasick(){
        t.emplace_back();
    }
    void add_string(string const &s){
        int v = 0;
        for (auto ch : s){
            int c = ch - 'a';
            if (t[v].next[c] == -1){
                t[v].next[c] = t.size();
                t.emplace_back();
            }
            v = t[v].next[c];
        }
        t[v].output = true;
    }
    void build(){

        queue<int> q;
        for (int c = 0; c < K; c++){
            if (t[0].next[c] != -1){
                t[0].go[c] = t[0].next[c];
                t[t[0].next[c]].link = 0;
                q.push(t[0].next[c]);
            } else {
                t[0].go[c] = 0;
            }
        }

        while(!q.empty()){
            int v = q.front();
            q.pop();
            t[v].output |= t[t[v].link].output;
            for (int c = 0; c < K; c++){
                if (t[v].next[c] != -1){
                    int u = t[v].next[c];
                    t[u].link = t[t[v].link].go[c];
                    t[v].go[c] = u;
                    q.push(u);
                } else {
                    t[v].go[c] = t[t[v].link].go[c];
                }
            }
        }

    }

};