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
int k = 30;
vector<string> debug = {"AA", "DD", "BB", "JJ", "HH", "EE", "CC"};

int bt(string node, int t, int inc, int acc, int depth = 0)
{
    int ret = -1;
    vis.insert(node);

    acc += inc;
    inc += rates[node];
    t += 1;
    // printf("node=%s t=%d inc=%d acc=%d\n", node.c_str(), t, inc, acc);

    for (auto [next, dist] : adj_dist[node])
    {
        // if (debug[depth + 1] != next)
        //     continue;
        if (vis.count(next) > 0)
            continue;
        if (rates[next] < 1)
            continue;

        if (t + dist > k)
        {
            max(ret, acc + ((k - t) * inc));
            continue;
        }

        int val = bt(
            next,
            t + dist,
            inc,
            acc + (inc * dist),
            depth + 1);
        ret = max(ret, val);
    }

    ret = max(ret, acc + ((k - t) * inc));
    vis.erase(node);
    assert(ret > 1);
    return ret;
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

    // return;
    int ans = 0;
    for (auto [next, dist] : adj_dist["AA"])
        if (rates[next] > 0)
            ans = max(ans, bt(next, dist, 0, 0, 1));
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