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

        as[c].insert(as[c].end(), as[b].end() - a, as[b].end());
        as[b].erase(as[b].end() - a, as[b].end());
    }

    for (auto &a : as)
        cout << a.back();
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("b.in", "r", stdin);
    solve();
}