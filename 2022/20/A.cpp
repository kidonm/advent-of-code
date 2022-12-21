#include <bits/stdc++.h>

using namespace std;

void solve()
{
    list<int> lst;
    vector<list<int>::iterator> ixs;

    int num;
    while (cin >> num)
        lst.push_back(num);

    auto it = lst.begin();
    for (int i = 0; i < (int)lst.size(); i++)
        ixs.push_back(it++);

    int n = (int)lst.size();
    for (int i = 0; i < n; i++)
    {
        auto &source = ixs[i];
        auto target = source;

        int offset = (*source) % (n - 1);
        if (offset < 0)
            offset += n - 1;

        for (int i = 0; i < offset; i++)
        {
            if (target == lst.end())
                target = lst.begin();
            target++;
        }
        if (offset != 0)
        {
            lst.erase(source);
            source = lst.insert(next(target), *source);
        }
    }

    int ans = 0;
    it = find(lst.begin(), lst.end(), 0);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            if (it == lst.end())
                it = lst.begin();
            it++;
        }
        ans += *it;
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("test.in", "r", stdin);
    freopen("a.in", "r", stdin);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}