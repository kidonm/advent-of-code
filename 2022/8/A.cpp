#include <bits/stdc++.h>

using namespace std;

vector<string> input, out;
long long ans = 0;
int m;
int n;

void solve()
{

    m = input.size();
    n = input[0].size();
    vector<string> empty_mat = vector(m + 2, string(n + 2, '.'));
    vector<string> dp_l = empty_mat;
    vector<string> dp_r = empty_mat;
    vector<string> dp_u = empty_mat;
    vector<string> dp_d = empty_mat;

    for (int i = 0; i < m; i++) // left to right prefix
        for (int j = 0; j < n; j++)
        {
            if (input[i][j] > dp_l[i + 1][j])
                out[i][j] = 'X';
            dp_l[i + 1][j + 1] = max(dp_l[i + 1][j], input[i][j]);
        }

    for (int i = 0; i < m; i++) // up to down prefix
        for (int j = 0; j < n; j++)
        {
            if (input[j][i] > dp_u[j][i + 1])
                out[j][i] = 'X';
            dp_u[j + 1][i + 1] = max(dp_u[j][i + 1], input[j][i]);
        }

    for (int i = 0; i < m; i++) // right to left prefix
        for (int j = n - 1; j >= 0; j--)
        {
            if (input[i][j] > dp_r[i + 1][j + 2])
                out[i][j] = 'X';
            dp_r[i + 1][j + 1] = max(dp_r[i + 1][j + 2], input[i][j]);
        }

    for (int i = m - 1; i >= 0; i--) // down to up prefix
        for (int j = 0; j < n; j++)
        {
            if (input[i][j] > dp_d[i + 2][j + 1])
                out[i][j] = 'X';
            dp_d[i + 1][j + 1] = max(dp_d[i + 2][j + 1], input[i][j]);
        }

    for (int i = 0; i < m; i++) // left to right prefix
        for (int j = 0; j < n; j++)
            if (out[i][j] == 'X')
                ans++;

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);

    string s;
    while (getline(cin, s))
        input.push_back(s);

    out = input;

    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}