#include <bits/stdc++.h>

using namespace std;

void solve()
{
    string s;
    long long ans = 0;
    long long acc = 0;
    while (getline(cin, s))
    {
        if (s.empty())
        {
            ans = max(ans, acc);
            acc = 0;
            continue;
        }
        stringstream ss(s);
        long long curr;
        ss >> curr;
        acc += curr;
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("./a.in", "r", stdin);
    solve();
}