#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int k = 14;
    int ans = -1;
    string s;
    cin >> s;
    deque<char> as;

    for (unsigned int i = 0; i < s.size(); i++)
    {
        if (i < k)
        {
            as.push_back(s[i]);
            continue;
        }

        as.pop_front();
        as.push_back(s[i]);

        set as_set = set<char>(as.begin(), as.end());
        if (as_set.size() == k)
        {
            ans = i;
            break;
        }
    }

    cout << ans + 1 << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("b.in", "r", stdin);
    solve();
}