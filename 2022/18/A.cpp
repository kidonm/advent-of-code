#include <bits/stdc++.h>

using namespace std;

int n = 25, z, y, x;
vector<vector<string>> in = vector(n, vector<string>(n, string(n, '.')));
uint64_t ans = 0;

vector<tuple<int, int, int>> ds = {
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 0},
    {0, 0, -1},
    {0, -1, 0},
    {-1, 0, 0},
};

void solve()
{
    while (cin >> z >> y >> x)
        in[z + 1][y + 1][x + 1] = '#';

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                if (in[i][j][k] == '#')
                    for (auto [dz, dy, dx] : ds)
                    {
                        int ii = i + dz, jj = j + dy, kk = k + dx;
                        if (ii >= 0 && ii < n &&
                            jj >= 0 && jj < n &&
                            kk >= 0 && kk < n &&
                            in[ii][jj][kk] == '.')
                            ans++;
                    }

    cout << ans << '\n';
}

// 4189
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("test.in", "r", stdin);
    freopen("a.in", "r", stdin);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}