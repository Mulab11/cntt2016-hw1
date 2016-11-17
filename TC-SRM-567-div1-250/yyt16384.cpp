#include <algorithm>
#include <vector>

class TheSquareRootDilemma {
  public:
    int countPairs(int N, int M);
};

int TheSquareRootDilemma::countPairs(int N, int M)
{
    int k = std::max(N, M);
    // x = c[x] * p^2, where c[x] is square-free
    std::vector<int> c(k + 1);
    for (int i = 1; i * i <= k; i++) {
        for (int j = i * i; j <= k; j += i * i) {
            c[j] = j / (i * i);
        }
    }
    std::vector<int> cnt1(k + 1);
    for (int i = 1; i <= N; i++) {
        cnt1[c[i]]++;
    }
    std::vector<int> cnt2(k + 1);
    for (int i = 1; i <= M; i++) {
        cnt2[c[i]]++;
    }
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        // Count pairs (x, y) where c[x] = c[y]
        ans += cnt1[i] * cnt2[i];
    }
    return ans;
}
