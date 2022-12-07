#include <bits/stdc++.h>

using namespace std;

vector<string> input;
unsigned int line = 0;
long long ans = 0;

long long walk()
{
    long long curr = 0;
    int size;
    while (line < input.size())
    {
        if (input[line][2] == 'l') // ls
        {
            line++;
            while (line < input.size() && input[line][0] != '$')
            {
                if (input[line][0] >= '0' && input[line][0] <= '9')
                {
                    stringstream ss(input[line]);
                    ss >> size;
                    curr += size;
                }
                line++;
            }
        }
        else if (input[line][2] == 'c') // cd
        {
            if (input[line][5] == '.') // cd ..
            {
                line++;
                if (curr <= 100000)
                    ans += curr;
                return curr;
            }
            else // cd somedir
            {
                line++;
                curr += walk();
            }
        }
        else
            assert(false && "Unknown command");
    }

    assert(false && "End");
}

void solve()
{
    line++;
    walk();
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    freopen("a.out.txt", "w", stdout);

    string s;
    while (getline(cin, s))
        input.push_back(s);

    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cerr << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}