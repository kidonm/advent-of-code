#include <bits/stdc++.h>

using namespace std;

void solve()
{
    string s;
    int ans = 0;
    while (getline(cin, s))
    {
        stringstream ss(s);
        char c1, c2;
        ss >> c1 >> c2;

        c2 -= ('X' - 'A') + 'A';
        c1 -= 'A';

        if (c1 == c2)
            ans += 3;
        else if ((c1 + 1) % 3 == c2)
            ans += 6;
        ans += c2 + 1;
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