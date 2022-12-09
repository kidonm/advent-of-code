#include <bits/stdc++.h>

using namespace std;

int n = 10000;
long long ans = 0;

void solve()
{
    vector<string> s = vector(n, string(n, '.'));

    char dir;
    int l, x, y, p, q;
    map<char, pair<int, int>> ds = {{'R', {0, 1}},
                                    {'L', {0, -1}},
                                    {'U', {-1, 0}},
                                    {'D', {1, 0}}};

    y = n / 2;
    x = n / 2;
    q = y;
    p = x;
    while (cin >> dir >> l)
    {
        cout << dir << ' ' << l << '\n';
        int dy = ds[dir].first;
        int dx = ds[dir].second;

        for (int i = 0; i < l; i++)
        {
            x += dx;
            y += dy;
            // s[y][x] = '*';

            if (abs(y - q) == 2 && x == p)
                q += y > q ? 1 : -1;
            else if (abs(x - p) == 2 && y == q)
                p += x > p ? 1 : -1;
            else if (x != p && y != q && abs(x - p) + abs(y - q) == 3)
            {
                if (abs(y - q) > 1)
                {
                    q = y + (y > q ? -1 : 1);
                    p = x;
                }
                else
                {
                    p = x + (x > p ? -1 : 1);
                    q = y;
                }
            }
            // else
            // {
            //     cout << abs(x - p) + abs(y - q) << '\n';
            //     assert(false && "Unexpected pos");
            // }

            s[q][p] = '#';
        }
    }

    for (string &row : s)
    {
        // cout << row << '\n';
        for (char &c : row)
            if (c == '#')
                ans++;
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    // freopen("a.out.txt", "w", stdout);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}