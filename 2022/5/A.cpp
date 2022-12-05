#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> as = {
    {'S', 'T', 'H', 'F', 'W', 'R'},
    {'S', 'G', 'D', 'Q', 'W'},
    {'B', 'T', 'W'},
    {'D', 'R', 'W', 'T', 'N', 'Q', 'Z', 'J'},
    {'F', 'B', 'H', 'G', 'L', 'V', 'T', 'Z'},
    {'L', 'P', 'T', 'C', 'V', 'B', 'S', 'G'},
    {'Z', 'B', 'R', 'T', 'W', 'G', 'P'},
    {'N', 'G', 'M', 'T', 'C', 'J', 'R'},
    {'L', 'G', 'B', 'W'},
};
void solve()
{
    string s;
    while (getline(cin, s))
    {
        stringstream ss(s);
        string skip;
        int a, b, c;
        ss >> skip >> a >> skip >> b >> skip >> c;
        b -= 1;
        c -= 1;

        for (int i = 0; i < a; i++)
        {
            as[c].push_back(as[b].back());
            as[b].pop_back();
        }
    }

    for (auto &a : as)
        cout << a.back();
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("./a.in", "r", stdin);
    solve();
}