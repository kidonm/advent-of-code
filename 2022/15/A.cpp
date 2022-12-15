#include <bits/stdc++.h>

using namespace std;

string skips;
char skipc;
// string out = string(30000000, '.');
// int ty = 2000000;
string out = string(30, '.');
int ty = 10;

void solve()
{
    int offset = 4;

    int x, y, p, q;
    while (
        cin >> skips >> skips               // sensor at
        >> skipc >> skipc                   // x=
        >> x >> skipc >> skipc >> skipc     // , y=
        >> y >> skipc                       // :
        >> skips >> skips >> skips >> skips // closest beacon is at
        >> skipc >> skipc                   // x=
        >> p >> skipc >> skipc >> skipc     // , y=
        >> q                                //
    )
    {
        int dx = abs(x - p);
        int dy = abs(y - q);
        int dty = abs(ty - y);

        if (y == ty)
            out[x + offset] = 'S';

        if (q == ty)
            out[p + offset] = 'B';

        if (dty < dx + dy)
        {
            int diff = dx + dy - dty;
            printf("%d %d\n", x - diff, x + diff);
            for (int i = x - diff + offset; i <= x + diff + offset; i++)
                if (out[i] == '.')
                    out[i] = '#';
        }
    }

    int ans = 0;
    for (int i = 0; i < out.size(); i++)
        if (out[i] == '#')
            ans++;
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("test.in", "r", stdin);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}