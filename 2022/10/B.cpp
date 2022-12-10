#include <bits/stdc++.h>

using namespace std;

vector<string> d = vector(6, string(40, '/'));
string instr;
int val;
long long acc = 1;

void solve()
{
    int cycle = 1;
    while (cin >> instr)
    {
        if (instr[0] == 'n')
        {
            if (((cycle % 40) - 1 >= acc - 1) && ((cycle % 40) - 1 <= acc + 1))
                d[cycle / 40][cycle % 40] = '#';
            else
                d[cycle / 40][cycle % 40] = ' ';
            cycle++;
            continue;
        }

        cin >> val;
        for (int i = 0; i < 2; i++)
        {
            if (((cycle % 40) - 1 >= acc - 1) && ((cycle % 40) - 1 <= acc + 1))
                d[cycle / 40][cycle % 40] = '#';
            else
                d[cycle / 40][cycle % 40] = ' ';
            cycle++;
        }
        acc += val;
    }
    for (auto &row : d)
        cout << row << '\n';
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