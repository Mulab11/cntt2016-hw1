#include <algorithm>
#include <unordered_set>
#include <utility>
#include <vector>

class Excavations {
  public:
    long long count(std::vector<int> kind, std::vector<int> depth, std::vector<int> found, int K);

  private:
    std::vector<long long> getCount(const std::vector<std::vector<int>> &c, int w);
};

long long Excavations::count(std::vector<int> kind, std::vector<int> depth, std::vector<int> found, int K)
{
    std::vector<std::vector<int>> c(found.size());
    std::vector<int> crem;
    for (int i = 0; i < (int)kind.size(); i++) {
        int r = -1;
        for (int j = 0; j < (int)found.size(); j++) {
            if (kind[i] == found[j]) {
                r = j;
                break;
            }
        }
        if (r != -1) {
            c[r].push_back(depth[i]);
        } else {
            crem.push_back(depth[i]);
        }
    }
    for (auto &x : c) {
        std::sort(x.begin(), x.end());
    }
    std::unordered_set<int> dvalues;
    for (auto x : depth) {
        dvalues.insert(x);
    }
    long long ans = 0;
    // Enumerate the largest depth among the first occurrence of found
    // kinds
    for (auto x : dvalues) {
        std::vector<long long> f1 = getCount(c, x);
        std::vector<long long> f2 = getCount(c, x - 1);
        int d = 0;
        for (auto p : crem) {
            if (p <= x) {
                d++;
            }
        }
        for (int i = 0; i < (int)f1.size(); i++) {
            long long s = f1[i] - f2[i];
            int u = kind.size() - found.size() - d - i;
            for (int j = 0; j < K - (int)found.size(); j++) {
                s *= u - j;
                s /= j + 1;
            }
            ans += s;
        }
    }
    return ans;
}

std::vector<long long> Excavations::getCount(const std::vector<std::vector<int>> &c, int w)
{
    // Return number of ways to choose the first occurrence of every
    // found kind, such that the number of unavailable elements is fixed
    // and all occurrences have a depth no more than w
    std::vector<long long> f = {1};
    for (const auto &x : c) {
        std::vector<long long> g(f.size() + x.size() - 1);
        for (int i = 0; i < (int)x.size() && x[i] <= w; i++) {
            for (int j = 0; j < (int)f.size(); j++) {
                g[j + i] += f[j];
            }
        }
        f = std::move(g);
    }
    return f;
}
