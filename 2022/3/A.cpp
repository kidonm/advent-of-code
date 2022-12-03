#include <bits/stdc++.h>

using namespace std;

void solve()
{
    string s;
    long long ans = 0;
    while (getline(cin, s))
    {
        auto mid = s.size() / 2;
        string s1 = s.substr(0, mid);
        string s2 = s.substr(mid);

        assert(s1.size() == s2.size());

        set set_s1(s1.begin(), s1.end());
        set set_s2(s2.begin(), s2.end());

        vector<char> intersection;
        set_intersection(set_s1.begin(), set_s1.end(),
                         set_s2.begin(), set_s2.end(),
                         back_inserter(intersection));

        char a = intersection[0];
        if (a >= 'A' && a <= 'Z')
            ans += a - 'A' + 27;
        else
            ans += a - 'a' + 1;
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    solve();
}