#include <bits/stdc++.h>

using namespace std;

class Tree
{
public:
    bool isLeaf() { return val != -1; };

    int val;
    Tree *parent;
    vector<Tree *> children;

    Tree(int val_, Tree *parent_) : val(val_), parent(parent_), children(vector<Tree *>()){};
    Tree(Tree *parent_) : val(-1), parent(parent_), children(vector<Tree *>()){};

    void print()
    {
        print_("");
    }

    void print_(string off)
    {
        if (val == -1)
            printf("%s -\n", off.c_str());
        else
            printf("%s %d\n", off.c_str(), val);
        for (auto c : children)
            c->print_(off + "  ");
    }
};

void parse(string &s, Tree *node)
{
    char c;
    int val;
    stringstream ss(s);
    while (ss >> c)
    {
        // cout << c << '\n';
        if (c == '[')
        {
            node->children.push_back(new Tree(node));
            node = node->children.back();
        }
        else if (c == ']')
        {
            node = node->parent;
        }
        else if (c == ',')
            continue;
        else
        {
            ss.putback(c);
            ss >> val;
            node->children.push_back(new Tree(val, node));
        }
    }
}

int cmp(Tree *l, Tree *r)
{
    int ans = 0;

    if (r->isLeaf() && l->isLeaf())
    {
        if (l->val == r->val)
            return 0;
        else if (l->val < r->val)
            return -1;
        else
            return 1;
    }

    if (r->isLeaf())
    {
        r->children.push_back(new Tree(r->val, r));
        r->val = -1;
        cmp(r, l);
    }
    if (l->isLeaf())
    {
        l->children.push_back(new Tree(l->val, l));
        l->val = -1;
        cmp(r, l);
    }

    for (unsigned int i = 0; ans == 0 && i < l->children.size() && i < r->children.size(); i++)
        ans = cmp(l->children[i], r->children[i]);

    if (ans == 0)
    {
        // cout << '\n';
        ans = (l->children.size() < r->children.size()) ? -1 : ans;
        ans = (l->children.size() > r->children.size()) ? 1 : ans;
    }

    return ans;
}

void solve()
{
    string s;

    vector<Tree *> input;
    while (cin >> s)
    {
        Tree *tmp = new Tree(nullptr);
        parse(s, tmp);
        input.push_back(tmp->children[0]);
    }

    string s1 = "[[2]]";
    Tree *t1 = new Tree(nullptr);
    parse(s1, t1);
    t1 = t1->children[0];

    string s2 = "[[6]]";
    Tree *t2 = new Tree(nullptr);
    parse(s2, t2);
    t2 = t2->children[0];

    int ans1 = 0;
    int ans2 = 0;

    for (auto &t : input)
    {
        if (cmp(t, t1) == -1)
        {
            // t->print();
            ans1++;
        }
        if (cmp(t, t2) == -1)
            ans2++;
    }

    cout << (ans1 + 1) * (ans2 + 2) << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("b.in", "r", stdin);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}