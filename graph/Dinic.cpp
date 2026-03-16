include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define all(a) (a).begin(), (a).end()
#define allr(a) (a).rbegin(), (a).rend()
#define pb push_back
#define S second
#define F first
#define int ll
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;
#define INF (ll)1e18
#define int ll

struct Edge{
    Edge(){}
    Edge(int v, int rev, int flow, int cap) : v(v), rev(rev), flow(flow), cap(cap) {}
    int v, rev;
    int flow, cap;
};
struct Dinic{

    vector<vector<Edge>> g;
    vector<int> level;
    vector<int> ptr;
    int n,s,t;
    Dinic(){}
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        g.assign(n,{});
        ptr.assign(n,0);
        level.assign(n,0);
    }
    void add_edge(int u,int v, int cap){
        g[u].pb({v,g[v].size(),0,cap});
        g[v].pb({u,g[u].size()-1,0,0});
    }
    bool bfs(){
        fill(level.begin(), level.begin()+n, -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for (auto [v,rev,flow,cap] : g[u]){
                if (level[v] == -1 && cap - flow > 0){
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }
    int dfs(int u, int pushed){
        if (pushed == 0)
            return 0;
        if (u == t)
            return pushed;
        for (int& j = ptr[u]; j < g[u].size(); j++){
            auto& edge = g[u][j];
            if(level[u] + 1 != level[edge.v] || edge.cap - edge.flow == 0) continue;
            int try_pushed = dfs(edge.v, min(pushed, edge.cap - edge.flow));
            if (try_pushed == 0) continue;
            edge.flow += try_pushed;
            g[edge.v][edge.rev].flow -= try_pushed;
            return try_pushed;
        }
        return 0;
    }
    int max_flow(){
        int flow = 0;
        while(bfs()){
            fill(all(ptr),0);
            while(int pushed = dfs(s,INF)){
                flow += pushed;
            }
        }
        return flow;
    }

};  

void solve() {
    
    int n,m; cin >> n >> m;
    Dinic dinic(n,0,n-1);
    for (int i = 0; i < m; i++){
        int u,v,w; cin >> u >> v >> w; u--, v--;
        dinic.add_edge(u,v,w);
    }
    cout << dinic.max_flow() << '\n';


}

int32_t main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();

    return 0;
}

