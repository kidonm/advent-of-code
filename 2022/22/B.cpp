#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> input;
int m = 50, n = 50;
string dirs;

// vector<vector<int>> fold = {
//     {0, 0, 1, 0},
//     {2, 3, 4, 0},
//     {0, 0, 5, 6},
// };

vector<vector<int>> fold = {
    {0, 1, 2},
    {0, 3, 0},
    {3, 4, 0},
    {5, 0, 0}};

map<int, pair<int, int>> face_to_offset = {
    {0, {0, 1}},
    {1, {0, 2}},
    {2, {1, 1}},
    {3, {2, 0}},
    {4, {2, 1}},
    {5, {3, 0}},
};

// vector<map<char, pair<int, int>>> adj = {
//     {
//         {'u', {1, 2}},
//         {'r', {5, 2}},
//         {'d', {3, 0}},
//         {'l', {2, 3}},
//     },
//     {
//         {'u', {0, 0 /*'d'*/}},
//         {'r', {2, 0 /*'r'*/}},
//         {'d', {4, 0 /*'u'*/}},
//         {'l', {5, 0 /*'u'*/}},
//     },
//     {
//         {'u', {0, 1 /*'r'*/}},
//         {'r', {3, 0 /*'r'*/}},
//         {'d', {4, 0 /*'r'*/}},
//         {'l', {1, 0 /*'l'*/}},
//     },
//     {
//         {'u', {0, 0 /*'u'*/}},
//         {'r', {5, 1 /*'d'*/}},
//         {'d', {4, 0 /*'d'*/}},
//         {'l', {2, 0 /*'l'*/}},
//     },
//     {
//         {'u', {3, 0 /*'u'*/}},
//         {'r', {5, 0 /*'r'*/}},
//         {'d', {1, 2 /*'u'*/}},
//         {'l', {2, 0 /*'u'*/}},
//     },
//     {
//         {'u', {3, 0 /*'l'*/}},
//         {'r', {0, 0 /*'l'*/}},
//         {'d', {1, 0 /*'r'*/}},
//         {'l', {4, 0 /*'l'*/}},
//     },
// };

vector<map<char, pair<int, int>>>
    adj = {
        {
            {'u', {5, 1}},
            {'r', {1, 0}},
            {'d', {2, 0}},
            {'l', {3, 2}},
        },
        {
            {'u', {5, 0}},
            {'r', {4, 2}},
            {'d', {2, 1}},
            {'l', {0, 0}},
        },
        {
            {'u', {0, 0}},
            {'r', {1, 3}},
            {'d', {4, 0}},
            {'l', {3, 3}},
        },
        {
            {'u', {2, 1}},
            {'r', {4, 0}},
            {'d', {5, 0}},
            {'l', {0, 2}},
        },
        {
            {'u', {2, 0}},
            {'r', {1, 2}},
            {'d', {5, 1}},
            {'l', {3, 0}},
        },
        {
            {'u', {3, 0}},
            {'r', {4, 3}},
            {'d', {1, 0}},
            {'l', {0, 3}},
        },
};

vector<char> ds_char = {'r', 'd', 'l', 'u'};
vector<pair<int, int>> ds_pair = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
map<char, int> char_to_dir = {{'r', 0}, {'d', 1}, {'l', 2}, {'u', 3}};

vector<string> out(fold.size() * m, string(fold[0].size() * n, '.'));

void init_out()
{
    int face = 0;

    for (int i = 0; i < fold.size(); i++)
    {
        for (int j = 0; j < fold[0].size(); j++)
        {
            int y_off = i * m;
            int x_off = j * n;
            bool is_face = fold[i][j] != 0;
            for (int k = 0; k < m; k++)
                for (int l = 0; l < n; l++)
                    out[y_off + k][x_off + l] = !is_face ? ' '
                                                         : input[face][k][l];

            if (is_face)
                face++;
        }
    }
}

void print(int f, int y, int x, int d)
{
    int face = 0;

    vector<string> tmp(fold.size() * m, string(fold[0].size() * n, '.'));

    for (int i = 0; i < fold.size(); i++)
    {
        for (int j = 0; j < fold[0].size(); j++)
        {
            int y_off = i * m;
            int x_off = j * n;
            bool is_face = fold[i][j] != 0;
            for (int k = 0; k < m; k++)
                for (int l = 0; l < n; l++)
                    tmp[y_off + k][x_off + l] = !is_face                        ? ' '
                                                : face == f && k == y && l == x ? d
                                                                                : input[face][k][l];

            if (is_face)
                face++;
        }
    }
    for (auto &row : tmp)
        cout << row << '\n';
    cout << '\n';

    int proj_y;
    int proj_x;

    for (int i = 0; i < tmp.size(); i++)
        for (int j = 0; j < tmp[0].size(); j++)
            if (tmp[i][j] >= 'a' && tmp[i][j] <= 'z')
            {
                proj_y = i;
                proj_x = j;
            }

    proj_y++;
    proj_x++;
    proj_y *= 1000;
    proj_x *= 4;

    int ans = proj_y + proj_x + char_to_dir[d];

    printf("%d %d %d ans=%d\n", proj_y, proj_x, char_to_dir[d], ans);
}

void read_input()
{
    vector<string> tmp;
    tmp.emplace_back();
    while (getline(cin, tmp.back()))
        tmp.emplace_back();

    tmp.pop_back();
    dirs = tmp.back();
    tmp.pop_back();

    for (int i = 0; i < fold.size(); i++)
    {
        for (int j = 0; j < fold[0].size(); j++)
        {
            if (fold[i][j] == 0)
                continue;

            vector<string> face(m, string(n, '.'));

            int y_off = i * m;
            int x_off = j * n;

            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    face[i][j] = tmp[y_off + i][x_off + j];

            input.push_back(face);
        }
    }
    // for (auto &face : input)
    // {
    //     for (auto &row : face)
    //     {
    //         cout << row << '\n';
    //     }
    //     cout << '\n';
    // }
    // cout << dirs << '\n';
}

tuple<int, int, int, int> edge(int f, int y, int x, int dir)
{
    int next_f = f, next_dir = dir, next_y = y, next_x = x;

    auto [adj_f, rot] = adj[f][ds_char[dir]];
    next_f = adj_f;
    next_dir = (dir + rot) % 4;

    for (int i = 0; i < rot; i++)
    {
        int tmp = next_x;
        next_x = m - next_y - 1;
        next_y = tmp;
        // printf("rot: %d %d\n", next_y, next_x);
    }

    if (ds_char[next_dir] == 'r')
        next_x = 0;
    else if (ds_char[next_dir] == 'd')
        next_y = 0;
    else if (ds_char[next_dir] == 'l')
        next_x = n - 1;
    else
        next_y = m - 1;

    return {next_f, next_y, next_x, next_dir};
}

void solve()
{
    // int yy = 0, xx = 1;
    // for (int i = 0; i < 4; i++)
    // {
    //     int tmp = xx;
    //     xx = m - 1 - yy;
    //     yy = tmp;

    //     printf("%d %d\n", yy, xx);
    // }

    // return;
    read_input();
    init_out();

    int f = 0, y = 0, x = 0, dir = 3, adv;
    char new_dir;
    stringstream dir_ss(dirs);
    // print(0, 0, 0, ds_char[dir]);
    int step = 1;
    while (dir_ss >> new_dir >> adv)
    {
        new_dir == 'L' ? dir-- : dir++;
        dir = dir % 4;
        if (dir < 0)
            dir = 3;

        // printf("step=%d adv=%d newd=%c\n", step, adv, new_dir);
        for (int i = 0; i < adv; i++)
        {
            auto [dy, dx] = ds_pair[dir];
            int next_f = f;
            int next_y = y + dy;
            int next_x = x + dx;
            int next_dir = dir;
            // printf("start - i=%d face=%d y=%d x=%d d=%c tile=%c\n", i, f, y, x, ds_char[dir], input[f][y][x]);
            if (next_y < 0 || next_y >= m || next_x < 0 || next_x >= n)
            {
                auto [ff, yy, xx, dd] = edge(f, y, x, dir);
                next_f = ff;
                next_y = yy;
                next_x = xx;
                next_dir = dd;

                // printf("edge - i=%d face=%d y=%d x=%d d=%c tile=%c\n", i, next_f, next_y, next_x, ds_char[next_dir], input[next_f][next_y][next_x]);
            }

            // printf("next - i=%d face=%d y=%d x=%d d=%c tile=%c\n", i, next_f, next_y, next_x, ds_char[next_dir], input[next_f][next_y][next_x]);

            if (input[next_f][next_y][next_x] == '.')
            {
                f = next_f;
                y = next_y;
                x = next_x;
                dir = next_dir;

                // print
                out[face_to_offset[f].first * m + y][face_to_offset[f].second * n + x] = ds_char[dir];

                // print(f, y, x, ds_char[dir]);
                continue;
            }
            // printf("break\n");
            break;
        }
        // print(f, y, x, ds_char[dir]);

        // if (step > 7)
        //     return;
        // for (auto &row : out)
        //     cout << row << '\n';
        // cout << '\n';
        // step++;
    }
    // for (auto &row : out)
    //     cout << row << '\n';
    // cout << '\n';
    print(f, y, x, ds_char[dir]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    // freopen("test.in", "r", stdin);
    freopen("out.txt", "w", stdout);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}

// 8432