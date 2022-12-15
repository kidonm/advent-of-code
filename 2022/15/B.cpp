#include <bits/stdc++.h>

using namespace std;

string skips;
char skipc;

void solve()
{
    vector<tuple<int, int, int, int>> ins;

    int x, y, p, q;
    long long ans, ans_y, ans_x;
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
        ins.push_back({x, y, p, q});
    }

    int N = 4000000;
    for (int i = 0; i < N; i++)
    {
        vector<pair<int, int>> line;
        for (unsigned int j = 0; j < ins.size(); j++)
        {
            auto &[x, y, p, q] = ins[j];
            int dx = abs(x - p);
            int dy = abs(y - q);
            int dty = abs(i - y);

            if (y == i)
                line.push_back({x, x});
            if (q == i)
                line.push_back({p, p});

            if (dty < dx + dy)
            {
                int diff = dx + dy - dty;
                line.push_back({x - diff, x + diff});
            }
        }
        sort(line.begin(), line.end(), [](pair<int, int> &a, pair<int, int> &b)
             { return a.first == b.first ? a.second < b.second : a.first < b.first; });

        auto prev = line[0];
        for (unsigned int j = 1; j < line.size(); j++)
        {
            auto curr = line[j];
            if (prev.first <= curr.first && prev.second >= curr.first && curr.second > prev.second)
                ;
            else if (prev.first <= curr.first && prev.second >= curr.second)
                continue;
            else if (prev.second == curr.first - 1)
                ;
            else
            {
                ans_y = i;
                ans_x = curr.first - 1;
            }

            prev = curr;
        }
    }
    ans = ans_x * N + ans_y;
    cout << ans_x << ' ' << ans_y << ' ' << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("b.in", "r", stdin);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}