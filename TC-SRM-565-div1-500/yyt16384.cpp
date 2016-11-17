#include <unordered_map>
#include <vector>

class TheDivisionGame {
  public:
    long long countWinningIntervals(int L, int R);
};

long long TheDivisionGame::countWinningIntervals(int L, int R)
{
    std::vector<int> val(R - L + 1);
    for (int i = 0; i < R - L + 1; i++) {
        val[i] = L + i;
    }
    std::vector<int> sg(R - L + 1);
    for (int i = 2; i * i <= R; i++) {
        for (int j = (L + i - 1) / i * i - L; j < R - L + 1; j += i) {
            while (val[j] % i == 0) {
                val[j] /= i;
                sg[j]++;
            }
        }
    }
    for (int i = 0; i < R - L + 1; i++) {
        if (val[i] > 1) {
            sg[i]++;
        }
    }
    std::vector<int> xors(R - L + 2);
    for (int i = 0; i < R - L + 1; i++) {
        xors[i + 1] = xors[i] ^ sg[i];
    }
    std::unordered_map<int, int> cntval;
    for (auto x : xors) {
        cntval[x]++;
    }
    long long ans = (long long)(R - L + 1) * (R - L + 2) / 2;
    // First player wins if xors[A] != xors[B + 1]
    for (auto x : cntval) {
        ans -= (long long)x.second * (x.second - 1) / 2;
    }
    return ans;
}
