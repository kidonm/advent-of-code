#include <bits/stdc++.h>

using namespace std;

string instr;
int val;
long long acc = 1;
long long ans = 0;
set<int> cycles = {20, 60, 100, 140, 180, 220};

void solve()
{
    int cycle = 1;
    while (cin >> instr)
    {
        if (instr[0] == 'n')
        {
            if (cycles.count(cycle))
                ans += cycle * acc;
            cycle++;
            continue;
        }

        cin >> val;
        for (int i = 0; i < 2; i++)
        {
            if (cycles.count(cycle))
                ans += cycle * acc;
            cycle++;
        }
        acc += val;
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}