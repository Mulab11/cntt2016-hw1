#include <algorithm>
#include <array>
#include <string>

class GooseTattarrattatDiv1 {
  public:
    int getmin(std::string S);

  private:
    static const int SZ = 26;
};

int GooseTattarrattatDiv1::getmin(std::string S)
{
    std::array<int, SZ> id;
    std::array<int, SZ> sumw = {0};
    std::array<int, SZ> maxw;
    for (int i = 0; i < SZ; i++) {
        id[i] = i;
    }
    for (auto x : S) {
        sumw[x - 'a']++;
    }
    maxw = sumw;
    for (int i = 0; i < (int)S.size() / 2; i++) {
        // Merge the two letters
        int x = S[i] - 'a';
        int y = S[S.size() - i - 1] - 'a';
        int u = id[x];
        int v = id[y];
        if (u != v) {
            for (int j = 0; j < SZ; j++) {
                if (id[j] == v) {
                    id[j] = u;
                }
            }
            sumw[u] += sumw[v];
            maxw[u] = std::max(maxw[u], maxw[v]);
        }
    }
    int ans = 0;
    for (int i = 0; i < SZ; i++) {
        if (id[i] == i) {
            // For each connected component, merge everything with the
            // letter with largest weight
            ans += sumw[i] - maxw[i];
        }
    }
    return ans;
}
