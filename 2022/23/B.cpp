#include <bits/stdc++.h>

using namespace std;

vector<string> input;
int padding = 500;
int m, n, o;

void print()
{
    for (auto &row : input)
        cout << row << '\n';
    cout << '\n';
}

map<char, vector<pair<int, int>>> rule_ds = {
    {'N', {{-1, 0}, {-1, -1}, {-1, 1}}},
    {'S', {{1, 0}, {1, -1}, {1, 1}}},
    {'W', {{0, -1}, {-1, -1}, {1, -1}}},
    {'E', {{0, 1}, {-1, 1}, {1, 1}}},
};
vector<char> rules = {'N', 'S', 'W', 'E'};
vector<pair<int, int>> actor_pos;
vector<int> actor_rules;

void solve()
{
    input.emplace_back();
    while (cin >> input.back())
        input.emplace_back();
    input.pop_back();

    for (string &row : input)
        row = string(padding, '.') + row + string(padding, '.');

    n = input[0].size();

    for (int i = 0; i < padding; i++)
    {
        input.insert(input.begin(), string(n, '.'));
        input.push_back(string(n, '.'));
    }

    m = input.size();

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (input[i][j] == '#')
            {
                actor_pos.push_back({i, j});
                actor_rules.push_back(0);
            }

    o = actor_pos.size();

    for (int k = 1; k <= 10000; k++)
    {
        // printf("%d\n", k);
        map<pair<int, int>, vector<int>> plan = {};

        for (int actor = 0; actor < o; actor++)
        {
            auto [y, x] = actor_pos[actor];
            bool clear = true;
            for (auto &[ignore, moves] : rule_ds)
                for (auto &[dy, dx] : moves)
                    clear = clear && input[y + dy][x + dx] == '.';

            if (clear)
            {
                actor_rules[actor] = (actor_rules[actor] + 1) % 4;
                continue;
            }

            int rule_ix = actor_rules[actor];
            bool can_move = false;
            for (int i = 0; i < 4 && !can_move; i++)
            {
                char rule = rules[(rule_ix + i) % 4];
                bool clear = true;
                for (auto [dy, dx] : rule_ds[rule])
                    clear = input[y + dy][x + dx] == '.' && clear;
                if (clear)
                {
                    can_move = true;
                    rule_ix = (rule_ix + i) % 4;
                    break;
                }
            }

            actor_rules[actor] = (actor_rules[actor] + 1) % 4;

            if (can_move)
            {
                auto [dy, dx] = rule_ds[rules[rule_ix % 4]][0];
                if (plan.find({y + dy, x + dx}) == plan.end())
                    plan.insert({make_pair(y + dy, x + dx), vector(0, 0)});
                plan[{y + dy, x + dx}].push_back(actor);
            }
        }

        if (plan.size() == 0)
        {
            printf("done k=%d\n", k);
            return;
        }

        for (auto &[key, actors] : plan)
        {
            auto [i, j] = key;
            if (actors.size() == 1)
            {
                int actor = actors[0];
                auto [curr_y, curr_x] = actor_pos[actor];
                input[curr_y][curr_x] = '.';
                input[i][j] = '#';
                actor_pos[actor] = {i, j};
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    // freopen("test.in", "r", stdin);
    // freopen("test2.in", "r", stdin);
    // freopen("out.txt", "w", stdout);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}