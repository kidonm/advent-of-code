#include <bits/stdc++.h>

using namespace std;

vector<vector<vector<pair<int, int>>>> state;
vector<vector<string>> game;
int m, n;
int loop;

void render(vector<string> &out)
{
    map<pair<int, int>, char> arrows = {
        {{0, 1}, '>'},
        {{0, -1}, '<'},
        {{-1, 0}, '^'},
        {{1, 0}, 'v'},
    };
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            auto tile = state[i][j];
            char c = tile.size() + '0';
            if (tile.size() == 0)
                c = '.';
            else if (tile.size() == 1)
                c = arrows[tile[0]];
            out[i][j] = c;
        }
}

void print(vector<string> board, int y, int x)
{
    board[y][x] = 'E';
    for (auto &row : board)
        cout << row << '\n';
}

void read_input()
{
    map<char, pair<int, int>> arrows = {
        {'>', {0, 1}},
        {'<', {0, -1}},
        {'^', {-1, 0}},
        {'v', {1, 0}},
    };
    vector<string> tmp;

    tmp.emplace_back();
    while (getline(cin, tmp.back()))
    {
        tmp.back().pop_back();
        tmp.back().erase(tmp.back().begin());
        tmp.emplace_back();
    }

    tmp.erase(tmp.begin());
    tmp.pop_back();
    tmp.pop_back();

    m = tmp.size();
    n = tmp[0].size();
    loop = lcm(m, n);

    state = vector(m, vector(n, vector(0, make_pair(0, 0))));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            if (tmp[i][j] == '.')
                continue;
            state[i][j].push_back(arrows[tmp[i][j]]);
        }
}

int t_max = 1000;
int bfs()
{
    vector<pair<int, int>> ds = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    queue<tuple<int, int, int>> q;
    q.push({0, -1, 0});
    set<tuple<int, int, int>> vis;

    while (!q.empty())
    {
        auto [t, y, x] = q.front();
        q.pop();
        if (vis.count({t, y, x}) > 0)
            continue;
        vis.insert({t, y, x});
        auto &board = game[(t + 1) % loop];

        if (t >= t_max)
            return -1;

        if (y == m - 1 && x == n - 1)
            return t + 1;

        vector<pair<int, int>> next_moves;
        for (auto &[dy, dx] : ds)
        {
            if (y + dy < 0 || y + dy >= m || x + dx < 0 || x + dx >= n || board[y + dy][x + dx] != '.')
                continue;
            next_moves.push_back({y + dy, x + dx});
        }

        if ((y == -1 && x == 0) || board[y][x] == '.')
            q.push({t + 1, y, x});

        for (auto [nexty, nextx] : next_moves)
            q.push({t + 1, nexty, nextx});
    }
}

void solve()
{
    read_input();
    for (int k = 1; k <= loop; k++)
    {
        game.push_back(vector(m, string(n, '.')));
        render(game.back());
        auto next = vector(m, vector(n, vector(0, make_pair(0, 0))));

        for (int y = 0; y < m; y++)
            for (int x = 0; x < n; x++)
            {
                if (state[y][x].size() == 0)
                    continue;
                for (auto &actor : state[y][x])
                {
                    auto &[dy, dx] = actor;
                    int nexty = (y + dy) % m;
                    int nextx = (x + dx) % n;
                    if (nexty < 0)
                        nexty = m - 1;
                    if (nextx < 0)
                        nextx = n - 1;
                    next[nexty][nextx].push_back(actor);
                }
            }
        state = next;
    }

    int ans = bfs();
    printf("ans=%d\n", ans);
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