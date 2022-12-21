#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll magic = 811589153;
list<ll> lst;
vector<list<ll>::iterator> ixs;
void solve()
{
    ll n = lst.size();
    for (auto it = lst.begin(); it != lst.end(); it++)
        ixs.push_back(it);

    for (ll round = 0; round < 10; round++)
    {
        // cout << "round:" << round << '\n';
        for (auto &source : ixs)
        {
            ll val = *source;

            ll offset = val % (n - 1);
            if (offset < 0)
                offset += n - 1;

            if (offset == 0)
                continue;

            auto target = source;
            for (ll j = 0; j < offset; j++)
                if (++target == lst.end())
                    target = lst.begin();
            lst.erase(source);
            source = lst.insert(next(target), val);
        }
        // for (auto e : lst)
        //     cout << e << ' ';
        // cout << '\n';
    }

    ll ans = 0;
    auto it = find(lst.begin(), lst.end(), 0);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            if (it == lst.end())
                it = lst.begin();
            it++;
        }
        ans += *it;
        cout << "ans:" << ans << ' ' << "curr:" << *it << '\n';
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("test.in", "r", stdin);
    freopen("a.in", "r", stdin);
    ll num;
    while (cin >> num)
        lst.push_back(num * magic);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}