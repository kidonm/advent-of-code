#include <bits/stdc++.h>

using namespace std;

class Tree
{
public:
    bool isLeaf;
    string name;
    long long size;
    Tree *parent;
    map<string, Tree *> children;

    Tree(bool isLeaf_, string name_, long long size_, Tree *parent_) : isLeaf(isLeaf_), name(name_), size(size_), parent(parent_), children(map<string, Tree *>()){};

    void print()
    {
        print_("");
    }

    void print_(string off)
    {
        printf("%s %s %llu\n", off.c_str(), name.c_str(), size);
        for (auto c : children)
            c.second->print_(off + "  ");
    }
};

void parse_left(string s, Tree *t);
void parse(Tree *t);

void parse_ls(Tree *root)
{
    cout << "parse ls" << '\n';
    string s;
    while (getline(cin, s) && s[0] != '$') // TODO the read line will need to be put back;
    {
        stringstream ss(s);
        cout << ss.str() << "\n";
        if (s[0] >= '0' && s[0] <= '9') // is a leaf
        {
            long long size;
            string name;
            ss >> size >> name;
            root->children.insert({name, new Tree(true, name, size, root)});
        }
        else if (s.substr(0, 3) == "dir")
        {
            string skip, name;
            ss >> skip >> name;
            root->children.insert({name, new Tree(false, name, 0, root)});
        }
        else
        {
            cout << s << "\n";
            assert(false);
        }
    }

    parse_left(s, root);
}

void parse_left(string s, Tree *root)
{
    cout << "parse left: " << s << '\n';
    if (s[0] == '$')
    {
        stringstream ss(s);
        string skip, op;
        ss >> skip >> op;
        if (op == "ls")
            parse_ls(root);
        else if (op == "cd")
        {
            string dir;
            ss >> dir;
            if (dir == "..")
                parse(root->parent);
            else
                parse(root->children[dir]);
        }
    }
}

void parse(Tree *root)
{
    cout << "parse:" << root->name << '\n';
    string s;
    getline(cin, s);

    if (s[0] == '$')
    {
        stringstream ss(s);
        string skip, op;
        ss >> skip >> op;
        if (op == "ls")
            parse_ls(root);
        else if (op == "cd")
        {
            string dir;
            ss >> dir;

            if (dir == "..")
                parse(root->parent);
            else
                parse(root->children[dir]);
        }
    }
}

long long ans = 0;

void dfs(Tree *t)
{
    for (auto &a : t->children)
    {
        dfs(a.second);
        if (!a.second->isLeaf && a.second->size <= 100000)
            ans += a.second->size;
        t->size += a.second->size;
    }
}

long long ans2 = 999999999999999999;

void dfs_2(Tree *t, long long rem)
{
    for (auto &a : t->children)
    {
        dfs_2(a.second, rem);
        if (!a.second->isLeaf && a.second->size + rem > 30000000)
            ans2 = min(ans2 + rem, a.second->size + rem) - rem;
    }
}

void solve()
{
    map<string, long long>();

    string s;
    getline(cin, s); // skip root
    Tree *t = new Tree(false, "/", 0, nullptr);
    parse(t);
    dfs(t);
    long long rem = 70000000 - t->size;
    dfs_2(t, rem);
    cout << ans << ' ' << ans2 << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("b.in", "r", stdin);
    solve();
}