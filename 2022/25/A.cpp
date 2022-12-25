#include <bits/stdc++.h>

using namespace std;

void solve()
{
    map<char, int> mapp = {
        {'2', 2},
        {'1', 1},
        {'0', 0},
        {'-', -1},
        {'=', -2},
    };
    map<int, char> rmapp = {
        {2, '2'},
        {1, '1'},
        {0, '0'},
        {-1, '-'},
        {-2, '='},
    };

    string in;
    int64_t acc = 0;
    while (cin >> in)
    {
        int64_t num = 0;
        for (unsigned int i = 0; i < in.size(); i++)
        {
            int64_t order = pow(5, i);
            num += order * mapp[in[in.size() - 1 - i]];
        }
        acc += num;
    }

    cout << "acc:" << acc << '\n';

    int64_t order = 5;
    int64_t carry = 0;
    string ans;
    while (acc != 0)
    {
        int64_t mod = ((acc + carry) % 5);
        acc = ((acc + carry) / 5);

        // printf("mod=(%lld) acc=%lld, carry=%lld\n", mod, acc, carry);
        if (mod > 2)
        {
            mod = mod - 5;
            carry = 1;
        }
        else if (mod < -2)
        {
            mod = mod + 5;
            carry = -1;
        }
        else
            carry = 0;

        ans.push_back(rmapp[mod]);

        order *= order;
    }

    if (carry != 0)
        ans.push_back(rmapp[carry]);

    reverse(ans.begin(), ans.end());
    cout << "ans:" << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    // freopen("test.in", "r", stdin);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}