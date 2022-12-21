#include <bits/stdc++.h>

using namespace std;

enum resource
{
    ore = 0,
    clay,
    obsidian,
    geode
};

vector<map<resource, map<resource, int>>> input;

void print_state(int t /*, map<string, map<string, int>> &costs*/, map<string, int> &robots, map<string, int> &resources)
{
    printf("t=%d robots=[", t);
    for (auto &[robot, count] : robots)
        printf("(%s, %d)", robot.c_str(), count);
    printf("] resources=[");
    for (auto &[resource, count] : resources)
        printf("(%s, %d)", resource.c_str(), count);
    cout << "]\n";
};

vector<int> bb(25, 0);
int max_t = 24;
void bt(int t, map<resource, map<resource, int>> &costs, map<resource, int> &robots, map<resource, int> &resources, set<resource> prev_skipped = {})
{
    // print_state(t, /*costs,*/ robots, resources);
    if (bb[t] > resources[geode])
        return;

    if (bb[t] < resources[geode])
        bb[t] = resources[geode];

    if (t >= max_t)
        return;

    set<resource> next_robots;
    for (auto &[robot, ignore] : robots)
    {
        bool clear = true;
        for (auto &[resource, cost] : costs[robot])
            clear = clear && resources[resource] >= cost;
        if (clear)
            next_robots.insert(robot);
    }

    for (auto &[robot, count] : robots)
        resources[robot] += count;

    bt(t + 1, costs, robots, resources, next_robots);
    for (resource next_robot : next_robots)
    {
        if (robots[clay] > 1 && next_robot == ore)
            continue;

        // if (next_robots.count(geode) > 0 && next_robot != geode)
        //     continue;

        if (prev_skipped.count(next_robot) > 0)
            continue;

        robots[next_robot] += 1;
        for (auto &[resource, count] : costs[next_robot])
            resources[resource] -= count;

        bt(t + 1, costs, robots, resources);

        for (auto &[resource, count] : costs[next_robot])
            resources[resource] += count;
        robots[next_robot] -= 1;
    }

    for (auto &[robot, count] : robots)
        resources[robot] -= count;
};

map<string, resource> ress = {
    {"ore", ore},
    {"clay", clay},
    {"obsidian", obsidian},
    {"geode", geode}};

void solve()
{
    string s;

    for (int i = 0; getline(cin, s); i++)
    {
        input.emplace_back();
        for (int j = 0; j < 4; j++)
        {
            getline(cin, s);
            stringstream ss(s);
            string skip, rob, mat;
            int count;

            ss >> skip >> rob >> skip >> skip; // each MAT robot costs
            input[i].insert({ress[rob], {}});
            while (ss >> count >> mat)
                input[i][ress[rob]].insert({ress[mat], count});
        }
    }

    int ans = 0;
    for (int i = 0; i < (int)input.size(); i++)
    {
        bb = vector(25, 0);
        map<resource, int> robots = {{ore, 1}, {clay, 0}, {obsidian, 0}, {geode, 0}};
        map<resource, int> resources = {{ore, 0}, {clay, 0}, {obsidian, 0}, {geode, 0}};
        bt(0, input[i], robots, resources);
        ans += (bb[24] * (i + 1));
        // cout << ans << '\n';
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("test.in", "r", stdin);
    freopen("a.in", "r", stdin);
    // freopen("out.txt", "w", stdout);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}
// T = 0
// map<string, int> robots = {{"ore", 1}, {"clay", 0}, {"obsidian", 0}, {"geode", 0}};
// map<string, int> resources = {{"ore", 0}, {"clay", 0}, {"obsidian", 0}, {"geode", 0}};
// T = 2
// map<string, int> robots = {{"ore", 1}, {"clay", 0}, {"obsidian", 0}, {"geode", 0}};
// map<string, int> resources = {{"ore", 2}, {"clay", 0}, {"obsidian", 0}, {"geode", 0}};
// T = 10
// map<string, int> robots = {{"ore", 1}, {"clay", 3}, {"obsidian", 0}, {"geode", 0}};
// map<string, int> resources = {{"ore", 4}, {"clay", 15}, {"obsidian", 0}, {"geode", 0}};
// T = 17
// map<string, int> robots = {{"ore", 1}, {"clay", 4}, {"obsidian", 2}, {"geode", 0}};
// map<string, int> resources = {{"ore", 3}, {"clay", 13}, {"obsidian", 8}, {"geode", 0}};
