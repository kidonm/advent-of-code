#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve()
{
    string s;
    ll ans = 0;
    while (getline(cin, s))
    {
        stringstream ss(s);
        ll a, b, c, d;
        char skip;
        ss >> a >> skip >> b >> skip >> c >> skip >> d;
        if ((a <= c && b >= d) || (c <= a && d >= b))
            ans++;
    }

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    solve();
}