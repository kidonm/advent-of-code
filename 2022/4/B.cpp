#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve()
{
    string s;
    ll ans = 0;
    while (getline(cin, s))
    {
        auto colon = s.find(',');
        auto dash1 = s.find('-', 0);
        auto dash2 = s.find('-', colon);

        s.replace(colon, 1, " ");
        s.replace(dash1, 1, " ");
        s.replace(dash2, 1, " ");

        stringstream ss(s);
        ll a, b, c, d;
        ss >> a >> b >> c >> d;
        if (b < c || d < a)
            continue;

        ans++;
    }

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("b.in", "r", stdin);
    solve();
}