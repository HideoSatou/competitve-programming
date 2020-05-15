#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

#define all(s) s.begin(), s.end()
#define ok puts("ok")
#define ll long long
#define pb push_back
#define mk make_pair
#define fr first
#define sc second
#define vi vector < int >
#define pi pair < int, int >
#define pii pair < int, pi >
#define next next123
#define left left123

const int N = 3e5 + 7;
const ll INF = 2e18 + 7;

ll t[16 * N], lz[16 * N];
ll cons;
int lf[16 * N], rf[16 * N], tim = 1;
int a[N], b[N], md[N];
int s, m, d, c, n;

void push (int v, int l, int r){
    if (l != r){
        if (!lf[v]){
            lf[v] = ++tim;
            rf[v] = ++tim;
        }
        lz[lf[v]] = min(lz[lf[v]], lz[v]);
        lz[rf[v]] = min(lz[rf[v]], lz[v]);
    }
    t[v] = min(t[v], lz[v]);
    lz[v] = INF;
}

void upd (int v, int l, int r, int ql, int qr, ll val){
    push(v, l, r);
    if (ql <= l && r <= qr){
        lz[v] = val;
        push(v, l, r);
        return;
    }
    if (r < ql || qr < l)
        return;
    int mid = (l + r) >> 1;
    if (!lf[v]){
        lf[v] = ++tim;
        rf[v] = ++tim;
    }
    upd(lf[v], l, mid, ql, qr, val);
    upd(rf[v], mid + 1, r, ql, qr, val);
    t[v] = min(t[lf[v]], t[rf[v]]);
}

ll get (int v, int l, int r, int ql, int qr){
    push(v, l, r);
    if (ql <= l && r <= qr)
        return t[v];
    if (r < ql || qr < l)
        return INF;
    int mid = (l + r) >> 1;
    if (!lf[v]){
        lf[v] = ++tim;
        rf[v] = ++tim;
    }
    return min(get(lf[v], l, mid, ql, qr), get(rf[v], mid + 1, r, ql, qr));
}

main(){
    cin >> s >> m >> d >> c >> n;
    memset(lz, 0x3f3f3f3f, sizeof(lz));
    memset(t, 0x3f3f3f3f, sizeof(t));
    for (int i = 1; i <= n; i++){
        scanf("%d%d", &a[i], &b[i]);
        md[i] = (m - a[i]) % d;
        md[i] = (d - md[i]) % d;
    }
    md[0] = (m - s) % d;
    md[0] = (d - md[0]) % d;
    cons = 1LL * ((m - s + d - 1) / d) * 1LL * c;
    upd(1, 0, d, 0, md[0], cons);
    upd(1, 0, d, md[0] + 1, d, cons + c);
    for (int i = 1; i <= n; i++){
        ll v1 = get(1, 0, d, 0, max(0, md[i] - 1)) + c - b[i];
        ll v2 = get(1, 0, d, md[i], d) - b[i];
        upd(1, 0, d, md[i], md[i], min(v1, v2));
    }
    cout << -get(1, 0, d, 0, d);
}
