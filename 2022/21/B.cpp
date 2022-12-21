#include <bits/stdc++.h>

using namespace std;

struct operation
{
    int64_t val;

    string left;
    string right;
    char op;
};

uint64_t eval(operation &node, map<string, operation> &ops)
{

    if (node.val == -1)
    {
        uint64_t eval_l = eval(ops[node.left], ops);
        uint64_t eval_r = eval(ops[node.right], ops);
        if (node.op == '+')
            return eval_l + eval_r;
        else if (node.op == '-')
            return eval_l - eval_r;
        else if (node.op == '*')
            return eval_l * eval_r;
        else if (node.op == '/')
            return eval_l / eval_r;
        else if (node.op == '=')
            return eval_l == eval_r;
        else
            assert(false && "unknown op");
    }
    else
        return node.val;
}

void solve()
{
    string node;

    map<string, operation> ops;

    while (cin >> node)
    {
        char c;
        cin >> c;
        cin.putback(c);

        operation op;
        op.val = -1;
        ops.insert({node, op});

        if (c >= '0' && c <= '9')
            cin >> ops[node].val;
        else
            cin >> ops[node].left >> ops[node].op >> ops[node].right;
    }

    ops["root"].op = '=';
    // Just try a couple of numbers and see how the left subtree value changes. Binsearch is not feasible but it can be found manually pretty easily.
    ops["humn"].val = 3441198826073;
    cout << eval(ops[ops["root"].left], ops) << ' ' << eval(ops[ops["root"].right], ops) << '\n';
    uint64_t ans = eval(ops["root"], ops);
    cout << ans << '\n';
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