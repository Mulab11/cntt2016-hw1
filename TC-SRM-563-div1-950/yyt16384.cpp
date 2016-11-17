#include <array>
#include <list>
#include <queue>
#include <string>
#include <utility>
#include <vector>

static int powermod(int x, int y, int m)
{
    int s = 1;
    while (y) {
        if (y & 1) {
            s = (long long)s * x % m;
        }
        x = (long long)x * x % m;
        y >>= 1;
    }
    return s;
}

class DFA {
  public:
    static const int SZ = 4;

    int n = 0;
    std::vector<char> accepted;
    std::vector<std::array<int, SZ>> next;
    std::vector<std::list<int>> ec;
    std::vector<int> ecid;
    std::vector<std::list<int>::iterator> ecpos;

    DFA() { }
    DFA(int n_) : n(n_), accepted(n), next(n) { }

    void getEquivalenceClasses();

  private:
    std::vector<int> partrefnewid;

    std::vector<std::pair<int, int>> partitionRefine(const std::vector<int> &c);
};

void DFA::getEquivalenceClasses()
{
    std::vector<std::array<std::vector<int>, SZ>> revedge(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < SZ; j++) {
            revedge[next[i][j]][j].push_back(i);
        }
    }
    ec.clear();
    ec.resize(2);
    ecid.resize(n);
    ecpos.resize(n);
    for (int i = 0; i < n; i++) {
        if (accepted[i]) {
            ec[0].push_front(i);
            ecid[i] = 0;
            ecpos[i] = ec[0].begin();
        } else {
            ec[1].push_front(i);
            ecid[i] = 1;
            ecpos[i] = ec[1].begin();
        }
    }
    partrefnewid.clear();
    partrefnewid.resize(n);
    std::queue<int> que;
    std::vector<char> inque(n);
    que.push(0);
    inque[0] = true;
    std::vector<int> valvis(n);
    int valvisn = 0;
    while (!que.empty()) {
        int x = que.front();
        std::list<int> ecxcopy = ec[x];
        que.pop();
        inque[x] = false;
        for (int i = 0; i < SZ; i++) {
            std::vector<int> vals;
            valvisn++;
            for (auto p : ecxcopy) {
                for (auto q : revedge[p][i]) {
                    if (valvis[q] != valvisn) {
                        valvis[q] = valvisn;
                        vals.push_back(q);
                    }
                }
            }
            std::vector<std::pair<int, int>> newparts = partitionRefine(vals);
            for (auto p : newparts) {
                if (inque[p.first] || ec[p.first].size() > ec[p.second].size()) {
                    que.push(p.second);
                    inque[p.second] = true;
                } else {
                    que.push(p.first);
                    inque[p.first] = true;
                }
            }
        }
    }
}

std::vector<std::pair<int, int>> DFA::partitionRefine(const std::vector<int> &c)
{
    std::vector<std::pair<int, int>> newparts;
    int oldecn = ec.size();
    std::vector<int> partvis;
    for (auto x : c) {
        int u = ecid[x];
        if (partrefnewid[u] >= 0) {
            partrefnewid[u] = -1;
            partvis.push_back(u);
        } else {
            partrefnewid[u]--;
        }
    }
    for (auto x : partvis) {
        if (-partrefnewid[x] == (int)ec[x].size()) {
            partrefnewid[x] = 0;
        } else {
            partrefnewid[x] = ec.size();
            ec.emplace_back();
            newparts.push_back(std::make_pair(x, partrefnewid[x]));
        }
    }
    for (auto x : c) {
        int u = ecid[x];
        int v = partrefnewid[u];
        if (v < oldecn) {
            continue;
        }
        ec[u].erase(ecpos[x]);
        ec[v].push_front(x);
        ecid[x] = v;
        ecpos[x] = ec[v].begin();
    }
    return newparts;
}

class CoinsGame {
  public:
    int ways(std::vector<std::string> board);

  private:
    static const int MOD = 1000000009;
};

int CoinsGame::ways(std::vector<std::string> board)
{
    static const int DIRS[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int n = board.size();
    int m = board[0].length();
    std::vector<std::vector<int>> id(n, std::vector<int>(m));
    int emptyn = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == '.') {
                id[i][j] = emptyn++;
            }
        }
    }
    DFA g(emptyn + 1);
    g.accepted[emptyn] = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == '.') {
                for (int k = 0; k < 4; k++) {
                    int x = i + DIRS[k][0];
                    int y = j + DIRS[k][1];
                    if (x < 0 || x >= n || y < 0 || y >= m) {
                        g.next[id[i][j]][k] = emptyn;
                    } else if (board[x][y] == '#') {
                        g.next[id[i][j]][k] = id[i][j];
                    } else {
                        g.next[id[i][j]][k] = id[x][y];
                    }
                }
            }
        }
    }
    g.getEquivalenceClasses();
    int ans = powermod(2, emptyn, MOD) - 1;
    for (int i = 0; i < (int)g.ec.size(); i++) {
        if (i != g.ecid[emptyn]) {
            // Choosing only cells in the same equivalence class is
            // invalid
            ans = (ans - powermod(2, g.ec[i].size(), MOD) + MOD + 1) % MOD;
        }
    }
    return ans;
}
