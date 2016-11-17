#include <algorithm>
#include <string>
#include <vector>

class MagicMolecule {
  public:
    int maxMagicPower(std::vector<int> magicPower, std::vector<std::string> magicBond);

  private:
    int recursiveGetMax(long long chosen, const std::vector<int> &w, const std::vector<long long> &badpairs);
};

int MagicMolecule::maxMagicPower(std::vector<int> magicPower, std::vector<std::string> magicBond)
{
    int n = magicPower.size();
    std::vector<long long> badpairs(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (magicBond[i][j] == 'N') {
                badpairs[i] |= 1LL << j;
                badpairs[j] |= 1LL << i;
            }
        }
    }
    return recursiveGetMax((1LL << n) - 1, magicPower, badpairs);
}

int MagicMolecule::recursiveGetMax(long long chosen, const std::vector<int> &w, const std::vector<long long> &badpairs)
{
    int cnt = 0;
    for (int i = 0; i < (int)w.size(); i++) {
        if ((chosen >> i) & 1) {
            cnt++;
        }
    }
    if (3 * cnt < 2 * (int)w.size()) {
        return -1;
    }
    int u = -1;
    int v = -1;
    // Find a pair of nodes that are not connected
    for (int i = 0; i < (int)w.size(); i++) {
        if ((chosen >> i) & 1) {
            long long es = badpairs[i] & chosen;
            if (es) {
                u = i;
                v = 0;
                while (!((es >> v) & 1)) {
                    v++;
                }
                break;
            }
        }
    }
    if (u == -1) {
        int ans = 0;
        for (int i = 0; i < (int)w.size(); i++) {
            if ((chosen >> i) & 1) {
                ans += w[i];
            }
        }
        return ans;
    }
    // Remove one of the nodes
    int ans1 = recursiveGetMax(chosen & ~(1LL << u), w, badpairs);
    int ans2 = recursiveGetMax(chosen & ~(1LL << v), w, badpairs);
    return std::max(ans1, ans2);
}
