#include <bits/stdc++.h>

using namespace std;

vector<deque<int>> s = {
    {52, 60, 85, 69, 75, 75},
    {96, 82, 61, 99, 82, 84, 85},
    {95, 79},
    {88, 50, 82, 65, 77},
    {66, 90, 59, 90, 87, 63, 53, 88},
    {92, 75, 62},
    {94, 86, 76, 67},
    {57},
};

vector<int (*)(int a)> fs = {
    [](int old)
    { return old * 17; },
    [](int old)
    { return old + 8; },
    [](int old)
    { return old + 6; },
    [](int old)
    { return old * 19; },
    [](int old)
    { return old + 7; },
    [](int old)
    { return old * old; },
    [](int old)
    { return old + 1; },
    [](int old)
    { return old + 2; },
};

vector<int (*)(int a)> ts = {
    [](int a)
    { return (a % 13) == 0 ? 6 : 7; },
    [](int a)
    { return (a % 7) == 0 ? 0 : 7; },
    [](int a)
    { return (a % 19) == 0 ? 5 : 3; },
    [](int a)
    { return (a % 2) == 0 ? 4 : 1; },
    [](int a)
    { return (a % 5) == 0 ? 1 : 0; },
    [](int a)
    { return (a % 3) == 0 ? 3 : 4; },
    [](int a)
    { return (a % 11) == 0 ? 5 : 2; },
    [](int a)
    { return (a % 17) == 0 ? 6 : 2; },
};

vector<int> out = {0, 0, 0, 0, 0, 0, 0};

int k = 20;

void solve()
{
    for (int i = 0; i < k; i++)
    {
        for (unsigned int m = 0; m < s.size(); m++)
        {
            while (!s[m].empty())
            {
                out[m]++;
                int item = s[m].front();
                s[m].pop_front();
                item = fs[m](item);
                item = item / 3;
                s[ts[m](item)].push_back(item);
            }

            // cout << "round: " << i << '\n';
            // for (unsigned int i = 0; i < s.size(); i++)
            // {
            //     printf("Monkey %d: ", i);
            //     for (unsigned int j = 0; j < s[i].size(); j++)
            //         cout << s[i][j] << ' ';
            //     cout << '\n';
            // }
            // cout << '\n';
            // if (m > 0)
            //     return;
        }

        // cout << "round: " << i << '\n';
        // for (unsigned int i = 0; i < s.size(); i++)
        // {
        //     printf("Monkey %d: ", i);
        //     for (unsigned int j = 0; j < s[i].size(); j++)
        //         cout << s[i][j] << ' ';
        //     cout << '\n';
        // }
    }
    for (unsigned int i = 0; i < out.size(); i++)
        cout << out[i] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}