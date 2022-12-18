#include <bits/stdc++.h>

using namespace std;

map<string, int> rates;
map<string, vector<string>> adj;
map<string, map<string, int>> adj_dist;

string skips, node, s;
int val;
char skipc;

void bfs(string start)
{
    deque<pair<string, int>> q = {{start, 0}};
    adj_dist.insert({start, {}});

    while (!q.empty())
    {
        auto [curr, dist] = q.front();
        adj_dist[start].insert({curr, dist});
        q.pop_front();
        for (auto next : adj[curr])
        {
            if (adj_dist[start].count(next) > 0)
                continue;

            q.push_back({next, dist + 1});
        }
    }
}

set<string> vis;
set<string> out;
int k = 26;

// 2107
int walk(vector<string> &path, int t, int inc, int acc, int d = 0)
{
    string &curr_node = path[d];

    acc += inc;
    inc += rates[curr_node];
    t += 1;
    // printf("node=%s t=%d inc=%d acc=%d\n", curr_node.c_str(), t, inc, acc);

    if (d + 1 == (int)path.size())
        return acc + ((k - t) * inc);

    string &next_node = path[d + 1];
    int next_distance = adj_dist[curr_node][next_node];

    if (t + next_distance > k)
        return acc + ((k - t) * inc);

    return walk(path, t + next_distance, inc, acc + (inc * next_distance), d + 1);
}

void solve()
{
    while (getline(cin, s))
    {
        stringstream ss(s);

        ss >> skips                                     // Valve
            >> node >> skips >> skips >> skips          // XX has flow rate
            >> val >> skips >> skips >> skips >> skips; // XX tunnels lead to valves

        rates.insert({node, val});
        adj.insert({node, {}});
        adj[node].emplace_back();
        while (ss >> adj[node].back())
            adj[node].emplace_back();
        adj[node].pop_back();
    }

    for (auto [node, rate] : rates)
        bfs(node);

    // vector<string> prev = {"DD", "JJ", "HH", "BB", "EE", "CC"};
    vector<string> prev;
    int prev_split = 0;
    for (auto [node, rate] : rates)
        if (rate > 0)
            prev.push_back(node);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, prev.size() - 1);

    int ans = 0;
    int max_iter = 100000;

    vector<string> curr;
    int curr_split = prev_split;
    for (int i = 0; i < max_iter; i++)
    {
        curr = prev;
        curr_split = prev_split;
        if (dist(gen) == 0) // change bisection point
        {

            int ix1 = 0, ix2 = 0;
            while (ix1 == ix2)
            {
                ix1 = dist(gen);
                ix2 = dist(gen);
            }

            string tmp = curr[ix1];
            curr[ix1] = curr[ix2];
            curr[ix2] = tmp;
        }
        else
        {
            curr_split = dist(gen);
            while (curr_split <= 0 || curr_split >= (int)curr.size() - 1)
                curr_split = dist(gen);
        }

        vector<string> curr1(curr.begin(), curr.begin() + curr_split);
        vector<string> curr2(curr.begin() + curr_split, curr.end());

        assert(curr1.size() + curr2.size() == curr.size());

        int curr_ans = 0;
        curr_ans += walk(curr1, adj_dist["AA"][curr1.front()], 0, 0, 0);
        curr_ans += walk(curr2, adj_dist["AA"][curr2.front()], 0, 0, 0);

        if (curr_ans >= ans)
        {
            ans = curr_ans;
            prev = curr;
            prev_split = curr_split;
        }

        if (i % 10000 == 0)
        {
            cout << "curr_split:" << curr_split << " ans:" << ans;
            cout << " nodes_a:";
            for (int i = 0; i < curr_split; i++)
                cout << prev[i] << ' ';
            cout << "nodes_b:";
            for (int i = curr_split; i < (int)prev.size(); i++)
                cout << prev[i] << ' ';
            cout << '\n';
        }
    }

    cout << "ans:" << ans << '\n';
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