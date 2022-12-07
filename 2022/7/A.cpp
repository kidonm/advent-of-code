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

void debug_cin()
{
    string s;
    cout << "Remaining cin:" << '\n';
    while (getline(cin, s))
        cout << s << "\\n"
             << '\n';
}

void parse(Tree *root)
{
    string s, skip, command, dir, name;
    int size;
    while (getline(cin, s))
    {
        if (s[0] == '$')
        {
            // ss >> skip >> command;
            if (s[2] == 'c')
            {
                // string dir = s.substr(5);
                if (s[5] == '.')
                    root = root->parent;
                else
                    root = root->children[s.substr(5)];
            }
        }
        else
        {
            stringstream ss(s);
            if (s[0] >= '0' && s[0] <= '9')
            {
                ss >> size >> name;
                root->size += size;
                // root->children.insert({name, new Tree(true, name, size, root)});
            }
            else
            {
                ss >> skip >> name;
                root->children.insert({name, new Tree(false, name, 0, root)});
            }
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

void solve()
{
    string s;
    getline(cin, s); // skip root
    Tree *t = new Tree(false, "/", 0, nullptr);
    parse(t);
    dfs(t);
    // t->print();
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("a.in", "r", stdin);
    auto start = std::chrono::high_resolution_clock::now();
    solve();
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << '\n';
}