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

void print_chamber(deque<string> &chamber, vector<pair<int, int>> &s, char c = '@')
{
    deque<string> out = chamber;
    for (auto &[y, x] : s)
        out[y][x] = c;
    for (string &row : out)
        cout << row << '\n';
}

int solve_1(int k0, bool debug = false)
{
    deque<string> chamber = {"+-------+"};
    int prev = 0;
    int prev_height = 0;
    int jet = 0;
    int k = 0;
    for (; k < k0; k++)
    {
        auto [s_height, s] = shapes[k % shapes.size()];
        for (auto &[y, x] : s)
            x += 3;

        for (int i = 0; i < 3 + s_height; i++)
            chamber.push_front(empty_row);

        bool stop = false;

        for (; !stop; jet++)
        {
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
                continue;
            }

            // print_chamber(s);
        }

        while (chamber[0] == empty_row)
            chamber.pop_front();

        if (chamber[0] == "|#####..|")
        {
            int curr_height = chamber.size() - 1;
            if (debug)
                printf("k=%d, loop=%d, height=%d, loop_height=%d\n", k, k - prev, curr_height, curr_height - prev_height);
            prev = k;
            prev_height = curr_height;
        }
    }

    int curr_height = chamber.size() - 1;
    if (debug)
        printf("k=%d, loop=%d, height=%d, loop_height=%d\n", k, k - prev, curr_height, curr_height - prev_height);
    return chamber.size() - 1;
}

void solve()
{
    cin >> input;

    // Run solve with debug to find out these periods
    uint64_t init_iter = 1425;
    uint64_t init_iter_height = 2263;
    uint64_t loop = 1745;
    uint64_t loop_height = 2783;
    uint64_t target = 1000000000000;
    // uint64_t target = 10000000;
    uint64_t full_iters = (target - init_iter) / loop;
    uint64_t rem = (target - init_iter) % loop;
    uint64_t rem_height = (uint64_t)solve_1(init_iter + rem) - init_iter_height;

    // cout << solve_1(target) << '\n';
    cout << "full iters:" << full_iters << '\n';
    cout << "iters height:" << full_iters * loop_height << '\n';
    cout << "init height:" << init_iter_height << '\n';
    cout << "rem:" << rem_height << '\n';
    cout << "ans:" << init_iter_height + rem_height + (full_iters * loop_height) << '\n';
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