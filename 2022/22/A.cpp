#include <bits/stdc++.h>

using namespace std;

vector<string> input;
int m, n;
string dirs;
vector<pair<int, int>> ds = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
map<pair<int, int>, char> dir_to_char = {{{0, 1}, 'r'}, {{1, 0}, 'd'}, {{0, -1}, 'l'}, {{-1, 0}, 'u'}};
map<char, int> dir_to_int = {{'r', 0}, {'d', 1}, {'l', 2}, {'u', 3}};

void print(vector<string> input, int y, int x, int d)
{
    input[y][x] = dir_to_char[ds[d]];
    for (string row : input)
        cout << row << '\n';
}

void read_input()
{
    string s;
    while (getline(cin, s))
    {
        if (s.empty())
            break;
        input.push_back(s);
    }
    m = input.size();

    size_t maxline = 0;
    for (int i = 0; i < m; i++)
        maxline = max(maxline, input[i].size());

    for (int i = 0; i < m; i++)
        if (input[i].size() < maxline)
            input[i] += string(maxline - input[i].size(), ' ');

    for (int i = 0; i < m; i++)
        assert(input[i].size() == maxline);

    for (int i = 0; i < m; i++)
    {
        input[i].insert(input[i].begin(), ' ');
        input[i] += ' ';
    }

    n = input[0].size();

    input.insert(input.begin(), string(m, ' '));
    input.push_back(string(m, ' '));

    getline(cin, dirs);
}

void solve()
{
    read_input();

    int y = 0;
    int x = 0;

    for (y = 0; y < m; y++)
    {
        for (x = 0; x < n; x++)
        {
            if (input[y][x] == ' ')
                continue;
            break;
        }

        if (input[y][x] == '.')
            break;
    }

    int d = 0;
    stringstream dir_ss(dirs);
    int adv, step = 0;
    char dir;
    print(input, y, x, d);
    while (dir_ss >> adv >> dir)
    {
        auto [dy, dx] = ds[d];
        // printf("adv=%d dy=%d dx=%d next_dir=%c\n", adv, dy, dx, dir);

        for (int i = 0; i < adv; i++)
        {
            if (input[y + dy][x + dx] == ' ')
            {
                // printf("walk back\n");
                int curr_y = y;
                int curr_x = x;
                while (input[y - dy][x - dx] != ' ')
                {
                    y -= dy;
                    x -= dx;
                }

                // printf("walked back %d %d\n", y, x);
                // print(input, y, x, d);

                if (input[y][x] != '.')
                {
                    y = curr_y;
                    x = curr_x;
                    break;
                }
            }
            else if (input[y + dy][x + dx] == '.')
            {
                y += dy;
                x += dx;
            }
            else
                break;
        }

        dir == 'L' ? d-- : d++;
        d = d % 4;
        if (d < 0)
            d = 3;

        // print(input, y, x, d);

        // if (step > 3)
        //     break;
        step++;
    }

    // printf("%d %d\n", y, x);
    int ans = (y * 1000) + (x * 4) + dir_to_int[dir_to_char[ds[d]]];

    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    // freopen("test.in", "r", stdin);
    // freopen("out.txt", "w", stdout);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}