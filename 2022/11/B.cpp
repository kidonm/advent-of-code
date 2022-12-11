#include <bits/stdc++.h>

using namespace std;

vector<deque<long long>> s = {
    {52, 60, 85, 69, 75, 75},
    {96, 82, 61, 99, 82, 84, 85},
    {95, 79},
    {88, 50, 82, 65, 77},
    {66, 90, 59, 90, 87, 63, 53, 88},
    {92, 75, 62},
    {94, 86, 76, 67},
    {57},
};

vector<long long (*)(long long a)> fs = {
    [](long long old)
    { return old * 17; },
    [](long long old)
    { return old + 8; },
    [](long long old)
    { return old + 6; },
    [](long long old)
    { return old * 19; },
    [](long long old)
    { return old + 7; },
    [](long long old)
    { return old * old; },
    [](long long old)
    { return old + 1; },
    [](long long old)
    { return old + 2; },
};

vector<map<bool, long long>> nexts = {
    {{true, 6LL}, {false, 7LL}},
    {{true, 0LL}, {false, 7LL}},
    {{true, 5LL}, {false, 3LL}},
    {{true, 4LL}, {false, 1LL}},
    {{true, 1LL}, {false, 0LL}},
    {{true, 3LL}, {false, 4LL}},
    {{true, 5LL}, {false, 2LL}},
    {{true, 6LL}, {false, 2LL}},
};

vector<long long> divs = {13LL, 7LL, 19LL, 2LL, 5LL, 3LL, 11LL, 17LL};

// vector<int (*)(int a)> ts = {
//     [](int a)
//     { return (a % 13) == 0 ? 6 : 7; },
//     [](int a)
//     { return (a % 7) == 0 ? 0 : 7; },
//     [](int a)
//     { return (a % 19) == 0 ? 5 : 3; },
//     [](int a)
//     { return (a % 2) == 0 ? 4 : 1; },
//     [](int a)
//     { return (a % 5) == 0 ? 1 : 0; },
//     [](int a)
//     { return (a % 3) == 0 ? 3 : 4; },
//     [](int a)
//     { return (a % 11) == 0 ? 5 : 2; },
//     [](int a)
//     { return (a % 17) == 0 ? 6 : 2; },
// };

// vector<deque<long long>> s = {
//     {79, 98},
//     {54, 65, 75, 74},
//     {79, 60, 97},
//     {74},
// };

// vector<long long (*)(long long a)> fs = {
//     [](long long old)
//     { return old * 19LL; },
//     [](long long old)
//     { return old + 6LL; },
//     [](long long old)
//     { return old * old; },
//     [](long long old)
//     { return old + 3LL; },
// };

// vector<map<bool, long long>> nexts = {
//     {{true, 2LL}, {false, 3LL}},
//     {{true, 2LL}, {false, 0LL}},
//     {{true, 1LL}, {false, 3LL}},
//     {{true, 0LL}, {false, 1LL}},
// };

// vector<long long> divs = {23LL, 19LL, 13LL, 17LL};

vector<long long> out = {0, 0, 0, 0, 0, 0, 0, 0};

int k = 10000;
// int magic = 96577;
int magic = 9699690;

void solve()
{
    for (int i = 1; i <= k; i++)
    {
        for (unsigned int m = 0; m < s.size(); m++)
        {
            while (!s[m].empty())
            {
                out[m]++;
                long long item = s[m].front();
                s[m].pop_front();
                item = fs[m](item);
                // item /= 3;
                bool comp = (item % divs[m]) == 0;
                s[nexts[m][comp]].push_back(item % magic);
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
        // cout << '\n';

        if (i % 1000 == 0 || i == 20 || i == 1)
        {
            printf("i: %d\n", i);
            for (unsigned int i = 0; i < out.size(); i++)
                cout << out[i] << '\n';
        }
    }
    // if (i % 1000 == 0 || i == 20 || i == 1)
    // printf("i: %d\n", i);
    // for (unsigned int i = 0; i < out.size(); i++)
    //     cout << out[i] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("b.in", "r", stdin);
    // auto start = std::chrono::high_resolution_clock::now();
    solve();
    // auto elapsed = std::chrono::high_resolution_clock::now() - start;
    // cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}