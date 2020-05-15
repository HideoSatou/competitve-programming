#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pb push_back
#define mk make_pair
#define fr first
#define sc second
#define vi vector < int >
#define vl vector < ll >
#define pi pair < int, int >
#define pl pair < ll, ll >
#define pii pair < int, pi >
#define vii vector < pi >
#define viii vector < pii >
 
const int N = 1e5 + 7;
const ll INF = 1e15 + 7;
 
ll d[5][N], ans;
ll x[N], y[N];
int s[5], us[N], c[N];
int n, m;
 
vii g[N];
 
void dijkstra (int id){
    priority_queue < pair < ll, int > > pq;
    pq.push(mk(0LL, s[id]));
    memset(d[id], 0x3f3f3f3f, sizeof d[id]);
    while(!pq.empty()){
        ll dis = -pq.top().fr; int cur = pq.top().sc;
        pq.pop();
        if (d[id][cur] < dis)
            continue;
        d[id][cur] = dis;
        for (pi to : g[cur]){
            if (d[id][to.fr] > dis + to.sc){
                d[id][to.fr] = dis + to.sc;
                pq.push(mk(-d[id][to.fr], to.fr));
            }
        }
    }
}
 
void calc (int v, ll dis = 0){
    us[v] = 1;
    for (pi to : g[v]){
        if (dis + to.sc != d[1][to.fr] || dis + to.sc + d[2][to.fr] != d[1][s[2]])
            continue;
        if (!us[to.fr])
            calc(to.fr, dis + to.sc);
        else
            c[to.fr]++;
    }
}
 
void dfs (int v, int p = 0, ll a = INF, ll b = INF, ll dis = 0){
    a = min(a, d[3][v]);
    b = min(b, d[4][v]);
    a = min(x[v], a);
    b = min(y[v], b);
    for (pi to : g[v]){
        if (to.sc + dis != d[1][to.fr] || dis + to.sc + d[2][to.fr] != d[1][s[2]])
            continue;
        if (c[to.fr]){
            c[to.fr]--;
            x[to.fr] = min(x[to.fr], a);
            y[to.fr] = min(y[to.fr], b);
        }
        else
            dfs(to.fr, v, a, b, dis + to.sc);
    }
    ll r = min(a + d[4][v], b + d[3][v]);
    ans = min(ans, r);
}
 
main (){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 4; i++)
        scanf("%d", &s[i]);
    for (int i = 1; i <= m; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        g[a].pb(mk(b, c));
        g[b].pb(mk(a, c));
    }
    for (int i = 1; i <= 4; i++)
        dijkstra(i);
    memset(x, 0x3f3f3f3f, sizeof x);
    memset(y, 0x3f3f3f3f, sizeof y);
    ans = d[3][s[4]];
    calc(s[1]);
    dfs(s[1]);
    printf("%lld", ans);
}
