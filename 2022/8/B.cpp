#include <bits/stdc++.h>

using namespace std;

vector<string> input;
long long ans = 0;
int m;
int n;

void solve()
{

    m = input.size();
    n = input[0].size();
    vector<pair<int, int>> ds = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int curr = input[i][j];
            long long curr_max = 1;
            for (pair<int, int> d : ds)
            {
                int ii = i;
                int jj = j;
                int dy = d.first;
                int dx = d.second;
                long long tmp = 0;

                while (ii + dy >= 0 && ii + dy < m && jj + dx >= 0 && jj + dx < n)
                {
                    tmp++;
                    if (input[ii + dy][jj + dx] >= curr)
                        break;

                    ii += dy;
                    jj += dx;
                }
                curr_max *= tmp;
            }
            ans = max(ans, curr_max);
        }
    }

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("b.in", "r", stdin);

    string s;
    while (getline(cin, s))
        input.push_back(s);

    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}