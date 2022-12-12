#include <bits/stdc++.h>

using namespace std;

string s;
vector<string> input;

int sy, sx, ey, ex, m, n;
vector<pair<int, int>> ds = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

typedef pair<int, int> ipair;

void solve()
{
    while (getline(cin, s))
        input.push_back(s);
    m = input.size();
    n = input[0].size();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (input[i][j] == 'S')
            {
                sy = i;
                sx = j;
            }
            if (input[i][j] == 'E')
            {
                ey = i;
                ex = j;
            }
        }
    }

    priority_queue<pair<int, ipair>, vector<pair<int, ipair>>, greater<pair<int, ipair>>> pq;
    vector<vector<int>> dists = vector(m, vector(n, INT_MAX));
    vector<string> prints = input;
    pq.push({0, {ey, ex}});

    while (!pq.empty())
    {
        auto [uy, ux] = pq.top().second;
        auto curr_distance = pq.top().first;
        prints[uy][ux] = input[uy][ux] - 'a' + 'A';
        pq.pop();

        for (auto &[dy, dx] : ds)
        {
            char curr_elev, next_elev;
            int nexty, nextx;
            nexty = uy + dy;
            nextx = ux + dx;

            if (nexty < 0 || nexty >= m || nextx < 0 || nextx >= n)
                continue;

            if (input[nexty][nextx] == 'S')
                next_elev = 'a';
            else if (input[nexty][nextx] == 'E')
                next_elev = 'z';
            else
                next_elev = input[nexty][nextx];

            if (input[uy][ux] == 'S')
                curr_elev = 'a';
            else if (input[uy][ux] == 'E')
                curr_elev = 'z';
            else
                curr_elev = input[uy][ux];

            if (curr_elev - next_elev > 1)
                continue;

            if (dists[nexty][nextx] > curr_distance + 1)
            {
                dists[nexty][nextx] = curr_distance + 1;
                pq.push({dists[nexty][nextx], {nexty, nextx}});
            }
        }
    }

    int ans = INT_MAX;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if (input[i][j] == 'a')
                ans = min(ans, dists[i][j]);

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("b.in", "r", stdin);
    freopen("out.txt", "w", stdout);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}