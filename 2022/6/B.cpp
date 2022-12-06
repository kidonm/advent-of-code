#include <bits/stdc++.h>

using namespace std;

void solve()
{
    unsigned int k = 14;
    int ans = -1;
    string s;
    cin >> s;
    unordered_map<char, int> as;
    deque<char> bs;

    for (unsigned int i = 0; i < s.size(); i++)
    {
        if (i < k)
        {
            auto search = as.find(s[i]);
            if (search == as.end())
                as.insert({s[i], 1});
            else
                search->second++;

            bs.push_back(s[i]);
            continue;
        }

        auto search = as.find(bs.front());
        if (--search->second == 0)
            as.erase(search->first);
        bs.pop_front();
        bs.push_back(s[i]);

        search = as.find(bs.back());
        if (search == as.end())
            as.insert({bs.back(), 1});
        else
            search->second++;

        if (as.size() == k)
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