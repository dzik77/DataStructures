#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>

vector<int> sorted_cyclic_shifts(const string &s){
    int n = s.size();
    vector<int> p(n), c(n), cnt(max(n,256));
    for (auto c : s)
        cnt[c]++;
    for (int i = 1; i < 256; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++){
        p[--cnt[s[i]]] = i;
    }
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++){
        if (s[p[i-1]] != s[p[i]]){
            classes++;
        }
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int lg = 0; (1 << lg) < n; lg++){
        for (int i = 0; i < n; i++){
            pn[i] = p[i] - (1 << lg);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(),cnt.begin()+classes,0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++){
            pii cur = {c[p[i]], c[(p[i] + (1 << lg)) % n]};
            pii prev = {c[p[i-1]], c[(p[i-1] + (1 << lg)) % n]};
            if (cur != prev)
                classes++;
            cn[p[i]] = classes - 1;
        }
        swap(c,cn);
    }
    return p;
}
vector<int> suffix_array(string s){
    s += '$';
    vector<int> sorted_shift = sorted_cyclic_shifts(s);
    sorted_shift.erase(sorted_shift.begin());
    return sorted_shift;
}