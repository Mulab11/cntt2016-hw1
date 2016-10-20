#include <algorithm>
#include <unordered_set>
#include <vector>

class MayTheBestPetWin {
  public:
    int calc(std::vector<int> A, std::vector<int> B);
};

int MayTheBestPetWin::calc(std::vector<int> A, std::vector<int> B)
{
    // sum(B in S) - sum(A in T) = sum(B) - sum(A+B in T)
    // sum(B in T) - sum(A in S) = sum(A+B in T) - sum(A)
    // So only sum(A+B in T) is relevant
    int suma = 0;
    for (auto x : A) {
        suma += x;
    }
    int sumb = 0;
    for (auto x : B) {
        sumb += x;
    }
    std::unordered_set<int> f = {0};
    for (int i = 0; i < (int)A.size(); i++) {
        int x = A[i] + B[i];
        std::vector<int> g;
        g.reserve(f.size());
        for (auto p : f) {
            g.push_back(p + x);
        }
        f.insert(g.begin(), g.end());
    }
    int ans = sumb;
    for (auto x : f) {
        ans = std::min(ans, std::max(sumb - x, x - suma));
    }
    return ans;
}
