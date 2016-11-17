#include <array>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Trie {
  public:
    static const int SZ = 26;

    std::vector<char> isstr = {false};
    std::vector<std::array<int, SZ>> edge{1};
    std::vector<int> fa = {-1};

    Trie();
    Trie(const std::vector<std::string> &strs);

    void addString(const std::string &s);
};

Trie::Trie()
{
    edge[0].fill(-1);
}

Trie::Trie(const std::vector<std::string> &strs) : Trie()
{
    for (const auto &x : strs) {
        addString(x);
    }
}

void Trie::addString(const std::string &s)
{
    int now = 0;
    for (auto c : s) {
        int x = c - 'a';
        if (edge[now][x] == -1) {
            edge[now][x] = isstr.size();
            isstr.push_back(false);
            edge.push_back(std::array<int, SZ>());
            edge.back().fill(-1);
            fa.push_back(now);
        }
        now = edge[now][x];
    }
    isstr[now] = true;
}

class SimilarNames {
  public:
    int count(std::vector<std::string> names, std::vector<int> info1, std::vector<int> info2);

  private:
    static const int MOD = 1000000007;

    int specnodecnt;
    std::vector<int> stateval;
    std::unordered_map<int, int> stateidmap;
    std::vector<std::vector<std::pair<int, int>>> statetrans;

    void initStates(const std::vector<std::pair<int, int>> &info);
    void initStateTrans();
    std::vector<int> recursiveDP(const Trie &trie, int x);
};

int SimilarNames::count(std::vector<std::string> names, std::vector<int> info1, std::vector<int> info2)
{
    Trie trie(names);
    std::vector<std::pair<int, int>> info;
    for (int i = 0; i < (int)info1.size(); i++) {
        info.push_back(std::make_pair(info1[i], info2[i]));
    }
    // Find possible states
    initStates(info);
    initStateTrans();
    std::vector<int> f = recursiveDP(trie, 0);
    int ans = f[stateval.size() - 1];
    // Remaining strings can be placed arbitrarily
    int rem = names.size() - specnodecnt;
    for (int i = 1; i <= rem; i++) {
        ans = (long long)ans * i % MOD;
    }
    return ans;
}

void SimilarNames::initStates(const std::vector<std::pair<int, int>> &info)
{
    std::unordered_map<int, int> specnodes;
    for (auto x : info) {
        if (specnodes.find(x.first) == specnodes.end()) {
            int p = specnodes.size();
            specnodes[x.first] = p;
        }
        if (specnodes.find(x.second) == specnodes.end()) {
            int p = specnodes.size();
            specnodes[x.second] = p;
        }
    }
    specnodecnt = specnodes.size();
    for (int i = 0; i < (1 << specnodecnt); i++) {
        // If info1[x] is in current subtree, info2[x] must also be in
        // this subtree
        bool ok = true;
        for (auto x : info) {
            if (((i >> specnodes[x.first]) & 1) && !((i >> specnodes[x.second]) & 1)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            stateidmap[i] = stateval.size();
            stateval.push_back(i);
        }
    }
}

void SimilarNames::initStateTrans()
{
    statetrans.resize(stateval.size());
    for (int i = 0; i < (int)stateval.size(); i++) {
        int x = stateval[i];
        for (int y = x; y != 0; y = (y - 1) & x) {
            int z = x & ~y;
            // The two parts must be both legal
            std::unordered_map<int, int>::const_iterator it1;
            std::unordered_map<int, int>::const_iterator it2;
            if ((it1 = stateidmap.find(y)) != stateidmap.end() && (it2 = stateidmap.find(z)) != stateidmap.end()) {
                statetrans[i].push_back(std::make_pair(it1->second, it2->second));
            }
        }
        statetrans[i].push_back(std::make_pair(0, i));
    }
}

std::vector<int> SimilarNames::recursiveDP(const Trie &trie, int x)
{
    // f[i] is the number of ways to choose state i from the subtree
    // rooted at x
    std::vector<int> f;
    for (auto y : trie.edge[x]) {
        if (y != -1) {
            std::vector<int> g = recursiveDP(trie, y);
            if (f.empty()) {
                f = std::move(g);
            } else {
                for (int i = stateval.size() - 1; i >= 0; i--) {
                    for (auto j : statetrans[i]) {
                        if (j.first != 0) {
                            f[i] = (f[i] + (long long)f[j.second] * g[j.first]) % MOD;
                        }
                    }
                }
            }
        }
    }
    if (f.empty()) {
        f.resize(stateval.size());
        f[0] = 1;
    }
    if (trie.isstr[x]) {
        // Place string x in one possible position
        for (int i = stateval.size() - 1; i >= 0; i--) {
            int p = stateval[i];
            for (int u = p & -p, tmp = p; u != 0; tmp &= ~u, u = tmp & -tmp) {
                int q = p & ~u;
                auto it = stateidmap.find(q);
                if (it != stateidmap.end()) {
                    f[i] = (f[i] + f[it->second]) % MOD;
                }
            }
        }
    }
    return f;
}
