#include <bits/stdc++.h>

struct SlownikPodslowBazowych
{
    std::vector<std::vector<int>> slowa;
    SlownikPodslowBazowych() {}
    SlownikPodslowBazowych(const std::string &slowo) {
        build(slowo);
    }
    int fast_log2(int n){
        return 31 - __builtin_clz(n);
    }
    void build(const std::string slowo){
        int j = fast_log2(slowo.size());
        slowa.assign(slowo.size(), std::vector<int>(j));
        for (int i = 0; i < slowo.size(); i++){
            slowa[i][0] = slowo[i] - 'a';
        }
        for (int l = 1; l < j; l++){
            std::vector<std::pair<int, int>> cand;
            for (int i = 0; i + (1 << l) <= slowo.size(); i++){
                cand.push_back({slowa[l-1][i], slowa[l-1][i+(1<<(l-1))]});
            }
            std::sort(cand.begin(), cand.end());
            cand.erase(std::unique(cand.begin(), cand.end()), cand.end());
            for (int i = 0; i + (1 << l) <= slowo.size(); i++){
                slowa[i][l] = std::lower_bound(cand.begin(), cand.end(), std::make_pair(slowa[l-1][i], slowa[l-1][i+(1<<(l-1))])) - cand.begin();
            }
        }
    }
    std::pair<int, int> get(int l, int r){
        int len = r - l + 1;
        int j = fast_log2(len);
        return {slowa[l][j], slowa[r-(1<<j)+1][j]};
    }
    bool compare(int l1, int r1, int l2, int r2){
        return get(l1, r1) == get(l2, r2);
    }
};

using namespace std;
#define all(x) x.begin(),x.end()
#define pii pair<int,int>
#define pb push_back
#define S second
#define F first
struct KMR{
    vector<vector<int>> rank;
    KMR(string s){
        int lg = 32 - __builtin_clz(s.size());
        rank.resize(lg, vector<int>(s.size()));
        vector<int> vals(s.size());
        for (int i = 0; i < s.size(); i++){
            vals[i] = s[i];
        }
        sort(all(vals));
        vals.erase(unique(all(vals)),vals.end());
        for (int i = 0; i < s.size(); i++){
            rank[0][i] = lower_bound(all(vals),s[i]) - vals.begin();
        }
        for (int k = 1; k < lg; k++){
            int len = 1 << (k-1);
            vector<pair<pii,int>> v;
            for (int i = 0; i < s.size() - (1 << k) + 1; i++){
                v.pb({{rank[k-1][i],rank[k-1][i + (1 << (k-1))]},i});
            }
            sort(all(v));
            int idx = 0;
            rank[k][v.front().S] = idx;
            for (int i = 1; i < v.size(); i++){
                if (v[i-1].F < v[i].F) idx++;
                rank[k][v[i].S] = idx;
            }
        }
    }
    int cmp(int i, int j, int len){
        int k = 31 - __builtin_clz(len);
        int p = (1 << k);
        pii A = {rank[k][i], rank[k][i+len-p]};
        pii B = {rank[k][j], rank[k][j+len-p]};
        if (A < B) return -1;
        if (A > B) return 1;
        return 0;
    }
};