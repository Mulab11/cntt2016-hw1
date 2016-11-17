#include <algorithm>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class UnknownTree {
  public:
    int getCount(std::vector<int> distancesA, std::vector<int> distancesB, std::vector<int> distancesC);

  private:
    static const int MOD = 1000000009;

    std::pair<int, int> getDistanceAB(const std::vector<int> &dista, const std::vector<int> &distb);
    int countTrees(const std::vector<int> &dista, const std::vector<int> &distb, const std::vector<int> &distc, int dab, int dac, int dbc);
};

int UnknownTree::getCount(std::vector<int> distancesA, std::vector<int> distancesB, std::vector<int> distancesC)
{
    std::pair<int, int> dab = getDistanceAB(distancesA, distancesB);
    std::pair<int, int> dac = getDistanceAB(distancesA, distancesC);
    std::pair<int, int> dbc = getDistanceAB(distancesB, distancesC);
    // It is also possible to have only node A between B and C, in which
    // case dist(B, C) = dist(A, B) + dist(A, C)
    std::unordered_set<int> xs = {dab.first, dab.second, dac.second + dbc.second};
    std::unordered_set<int> ys = {dac.first, dac.second, dab.second + dbc.second};
    std::unordered_set<int> zs = {dbc.first, dbc.second, dab.second + dac.second};
    int ans = 0;
    for (auto x : xs) {
        for (auto y : ys) {
            for (auto z : zs) {
                ans = (ans + countTrees(distancesA, distancesB, distancesC, x, y, z)) % MOD;
            }
        }
    }
    return ans;
}

std::pair<int, int> UnknownTree::getDistanceAB(const std::vector<int> &dista, const std::vector<int> &distb)
{
    // If there is any node i on the path (A, B), dist(A, B) = dista[i]
    // + distb[i]. If there is any node i in subtree A or B, dist(A, B)
    // = abs(dista[i] - distb[i])
    int minsum = INF;
    int maxdiff = -INF;
    for (int i = 0; i < (int)dista.size(); i++) {
        minsum = std::min(minsum, dista[i] + distb[i]);
        maxdiff = std::max(maxdiff, std::abs(dista[i] - distb[i]));
    }
    return std::make_pair(minsum, maxdiff);
}

int UnknownTree::countTrees(const std::vector<int> &dista, const std::vector<int> &distb, const std::vector<int> &distc, int dab, int dac, int dbc)
{
    if (dab == 0 || dac == 0 || dbc == 0) {
        return 0;
    }
    if ((dab + dac + dbc) % 2) {
        return 0;
    }
    int lcadist = (dab + dac - dbc) / 2;
    if (lcadist < 0 || lcadist > dab || lcadist > dac) {
        return 0;
    }
    std::unordered_map<int, std::vector<int>> subtrdeps;
    // Node A, B, C are already added
    subtrdeps[0].push_back(0);
    subtrdeps[dab].push_back(0);
    subtrdeps[dac == lcadist ? lcadist : dab + dac - lcadist].push_back(0);
    for (int i = 0; i < (int)dista.size(); i++) {
        // Find the subtree this node is in
        if ((dista[i] + distb[i] + dab) % 2) {
            return 0;
        }
        int posab = (dista[i] - distb[i] + dab) / 2;
        if (posab < 0 || posab > dab) {
            return 0;
        }
        if ((dista[i] + distc[i] + dac) % 2) {
            return 0;
        }
        int posac = (dista[i] - distc[i] + dac) / 2;
        if (posac < 0 || posac > dac) {
            return 0;
        }
        int idx;
        int idxdist;
        if (posab <= lcadist && posab == posac) {
            idx = posab;
            idxdist = posab;
        } else if (posac == lcadist && posab > lcadist) {
            idx = posab;
            idxdist = posab;
        } else if (posab == lcadist && posac > lcadist) {
            idx = dab + posac - lcadist;
            idxdist = posac;
        } else {
            return 0;
        }
        int dep = dista[i] - idxdist;
        if (dep < 0) {
            return 0;
        }
        subtrdeps[idx].push_back(dep);
    }
    if (subtrdeps.find(lcadist) == subtrdeps.end()) {
        // LCA must be a node
        return 0;
    }
    int ans = 1;
    for (const auto &x : subtrdeps) {
        std::vector<int> c = x.second;
        std::sort(c.begin(), c.end());
        if (c[0] != 0) {
            return 0;
        }
        int pre = 0;
        for (int i = 1; i < (int)c.size(); i++) {
            while (pre < i && c[pre] < c[i]) {
                pre++;
            }
            // Choose any of the nodes with lower depth as father
            ans = (long long)ans * pre % MOD;
        }
    }
    return ans;
}
