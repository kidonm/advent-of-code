#include <bits/stdc++.h>

using namespace std;

int n = 1000;
int k = 10;
long long ans = 0;

void solve()
{
    vector<string> s = vector(n, string(n, '.'));

    char dir;
    int l;
    vector<int> ys = vector(k, n / 2);
    vector<int> xs = vector(k, n / 2);
    map<char, pair<int, int>> ds = {{'R', {0, 1}},
                                    {'L', {0, -1}},
                                    {'U', {-1, 0}},
                                    {'D', {1, 0}}};

    while (cin >> dir >> l)
    {
        // cout << dir << ' ' << l << '\n';
        int dy = ds[dir].first;
        int dx = ds[dir].second;

        // for (string &row : s)
        //     cout << row << '\n';
        // cout << '\n';

        for (int i = 0; i < l; i++)
        {
            // s[ys[0]][xs[0]] = '0';
            ys[0] += dy;
            xs[0] += dx;

            for (int j = 1; j < k; j++)
            {
                int y, x, q, p;
                y = ys[j - 1];
                x = xs[j - 1];
                q = ys[j];
                p = xs[j];

                if (abs(y - q) == 2 && x == p)
                    q += y > q ? 1 : -1;
                else if (abs(x - p) == 2 && y == q)
                    p += x > p ? 1 : -1;
                else if (x != p && y != q && abs(x - p) + abs(y - q) > 2)
                {
                    if (abs(y - q) == 2 && abs(x - p) == 1)
                    {
                        q = y + (y > q ? -1 : 1);
                        p = x;
                    }
                    else if (abs(x - p) == 2 && abs(y - q) == 1)
                    {
                        p = x + (x > p ? -1 : 1);
                        q = y;
                    }
                    else if (abs(x - p) == 2 && abs(y - q) == 2)
                    {
                        p = p + (x > p ? 1 : -1);
                        q = q + (y > q ? 1 : -1);
                    }
                    // else
                    // {
                    //     q = y - q;
                    //     p = x - p;
                    // }
                }
                if (j == 9)
                    s[q][p] = '#';
                // s[ys[j]][xs[j]] = '.';
                // s[q][p] = j + '0';
                ys[j] = q;
                xs[j] = p;
            }
        }
    }

    cout << "P1" << '\n';
    cout << "600 600" << '\n';
    for (string &row : s)
    {
        for (char c : row.substr(0, 600))
        {
            if (c == '#')
                cout << "0 ";
            else
                cout << "1 ";
        }
        cout << '\n';
    }
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("b.in", "r", stdin);
    freopen("out.pgm", "w", stdout);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    // auto elapsed = std::chrono::high_resolution_clock::now() - start;
    // cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}