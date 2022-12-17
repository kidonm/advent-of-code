#include <bits/stdc++.h>

using namespace std;

string input;
vector<pair<int, vector<pair<int, int>>>> shapes = {
    {1, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}},         // -
    {3, {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}}}, // +
    {3, {{2, 0}, {2, 1}, {2, 2}, {1, 2}, {0, 2}}}, // ⅃
    {4, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},         // |
    {2, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}},         // #
};

map<char, int> ds = {{'<', -1}, {'>', 1}};
string empty_row = "|.......|";
deque<string> chamber = {"+-------+"};

void print_chamber(vector<pair<int, int>> &s, char c = '@')
{
    deque<string> out = chamber;
    for (auto &[y, x] : s)
        out[y][x] = c;
    for (string &row : out)
        cout << row << '\n';
}

void solve()
{
    cin >> input;

    int prev = -1;
    int jet = 0;
    for (int k = 0; k < 2022; k++)
    {
        auto [s_height, s] = shapes[k % shapes.size()];
        for (auto &[y, x] : s)
            x += 3;

        for (int i = 0; i < 3 + s_height; i++)
            chamber.push_front(empty_row);

        bool stop = false;

        // print_chamber(s);

        for (; !stop; jet++)
        {
            // printf("step=%d\n", jet);
            int dx = ds[input[jet % input.size()]];
            bool clear = true;
            for (auto &[y, x] : s)
                clear = clear && chamber[y][x + dx] == '.';
            if (clear)
                for (auto &[y, x] : s)
                    x += dx;

            clear = true;
            for (auto &[y, x] : s)
                clear = clear && chamber[y + 1][x] == '.';

            if (clear)
                for (auto &[y, x] : s)
                    y += 1;
            else
            {
                for (auto &[y, x] : s)
                    chamber[y][x] = '#';
                stop = true;
                // print_chamber(s, '#');
                continue;
            }

            // print_chamber(s);
        }

        while (chamber[0] == empty_row)
            chamber.pop_front();

        // if (chamber[0] == "|#####..|")
        // {
        //     printf("loop=%d, jet=%d iter:%d\n", jet - prev, jet, jet % input.size());
        //     prev = jet;
        // }
    }

    cout << chamber.size() - 1 << '\n';
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