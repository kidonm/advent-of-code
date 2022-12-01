#include <bits/stdc++.h>

using namespace std;

void solve()
{
    string s;
    vector<long long> ans;
    long long acc = 0;
    while (getline(cin, s))
    {
        if (s.empty())
        {
            ans.push_back(acc);
            acc = 0;
            continue;
        }
        stringstream ss(s);
        long long curr;
        ss >> curr;
        acc += curr;
    }
    sort(ans.rbegin(), ans.rend());
    cout << ans[0] + ans[1] + ans[2] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("./a.in", "r", stdin);
    solve();
}