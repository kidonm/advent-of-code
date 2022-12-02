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

        c2 -= 'X';
        c1 -= 'A';

        if (c2 == 0)
            ans += ((c1 - 1) < 0) ? 2 : c1 - 1;
        else if (c2 == 1)
            ans += c1 + 3;
        else
            ans += ((c1 + 1) % 3) + 6;

        ans += 1;
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