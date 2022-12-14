#include <bits/stdc++.h>

using namespace std;

string s;
int m = 200;
int n = 600;
vector<string> input = vector(m, string(n, '.'));

void solve()
{
    while (getline(cin, s))
    {
        stringstream ss(s);
        int x, y, prevx, prevy;
        char skipc;
        string skips;
        ss >> x >> skipc >> y;
        input[y][x] = '#';
        prevx = x;
        prevy = y;
        while (ss >> skips >> x >> skipc >> y)
        {
            while (abs(prevx - x) > 0)
            {
                input[y][prevx] = '#';
                prevx = prevx + (x > prevx ? 1 : -1);
            }
            while (abs(prevy - y) > 0)
            {
                input[prevy][x] = '#';
                prevy = prevy + (y > prevy ? 1 : -1);
            }

            input[prevy][prevx] = '#';
        }
    }

    input[0][500] = '+';

    bool quit = false;
    int ans = 0;
    while (!quit)
    {
        int startx = 500;
        int starty = 1;

        while (!quit)
        {
            if (starty + 1 >= m)
            {
                cout << "Fall out!" << '\n';
                quit = true;
                break;
            }

            if (input[starty + 1][startx] == '.')
            {
                starty++;
            }
            else if (input[starty + 1][startx - 1] == '.')
            {
                starty++;
                startx--;
            }
            else if (input[starty + 1][startx + 1] == '.')
            {
                starty++;
                startx++;
            }
            else
            {
                input[starty][startx] = 'o';
                ans++;
                break;
            }
        }
    }
    // for (string &row : input)
    //     cout << row << '\n';
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    freopen("out.txt", "w", stdout);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}