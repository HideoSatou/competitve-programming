#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

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
#define prev prev123
#define next next123
#define pow pow123
#define left left123
#define right right123

const int N = 2007;
const int INF = 1e9 + 7;

int a[N], dp[N][N];
int n, p, q;

bool check (int w){
    memset(dp, 0, sizeof(dp));
    dp[0][0] = q;
    int l1 = 1, l2 = 1;
    for (int i = 1; i <= n; i++){
        while (a[i] - a[l1] + 1 > w)
            l1++;
        while (a[i] - a[l2] + 1 > 2 * w)
            l2++;
        for (int j = 0; j <= p; j++){
            dp[i][j] = dp[l2 - 1][j] - 1;
            if (j)
                dp[i][j] = max(dp[i][j], dp[l1 - 1][j - 1]);
        }
    }
    if (dp[n][p] >= 0)
        return true;
    return false;
}

main(){
    cin >> n >> p >> q;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    if (p + q >= n){
        puts("1");
        return 0;
    }
    sort(a + 1, a + n + 1);
    int l = 0, r = INF;
    while (l + 1 < r){
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    printf("%d", r);
}
