#include <bits/stdc++.h>

using namespace std;

void solve()
{
    string s;
    long long ans = 0;
    while (getline(cin, s))
    {
        set set_int(s.begin(), s.end());
        for (int i = 0; i < 2; i++)
        {
            string s1;
            getline(cin, s1);
            vector<char> intersection;
            set set_s1(s1.begin(), s1.end());
            set_intersection(set_s1.begin(), set_s1.end(),
                             set_int.begin(), set_int.end(),
                             back_inserter(intersection));
            set_int = set<char>(intersection.begin(), intersection.end());
        }
        char a = (*set_int.begin());
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
    freopen("b.in", "r", stdin);
    solve();
}