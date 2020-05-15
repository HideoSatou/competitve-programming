#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define fr first
#define sc second

const int N = 3e5 + 7;

pair < ll, int > a[N];
ll t[4 * N];
ll ans;
int n;

void upd (int v, int l, int r, int pos){
    if (l == r)
        t[v] = 1;
    else {
        int mid = (l + r) >> 1;
        if (pos <= mid)
            upd(v + v, l, mid, pos);
        else
            upd(v + v + 1, mid + 1, r, pos);
        t[v] = t[v + v] + t[v + v + 1];
    }
}

ll get (int v, int l, int r, int ql, int qr){
    if (ql <= l && r <= qr)
        return t[v];
    if (r < ql || qr < l)
        return 0LL;
    int mid = (l + r) >> 1;
    return get(v + v, l, mid, ql, qr) + get(v + v + 1, mid + 1, r, ql, qr);
}

main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i].fr;
        a[i].sc = i;
    }
    sort(a + 1, a + n + 1);
    int l = 1;
    for (int i = 1; i <= n; i++){
        if (a[i].fr != a[i - 1].fr)
            for (l; l < i; l++)
                upd(1, 1, n, a[l].sc);
        ans += get(1, 1, n, 1, a[i].sc) * get(1, 1, n, a[i].sc, n);
    }
    cout << ans;
}
