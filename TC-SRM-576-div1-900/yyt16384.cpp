#include <algorithm>
#include <string>
#include <unordered_set>
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

class CharacterBoard {
  public:
    int countGenerators(std::vector<std::string> fragment, int W, int i0, int j0);

  private:
    static const int MOD = 1000000009;
    static const int SZ = 26;

    std::vector<long long> divisors(long long x);
};

int CharacterBoard::countGenerators(std::vector<std::string> fragment, int W, int /*i0*/, int /*j0*/)
{
    int n = fragment.size();
    int m = fragment[0].length();
    // Lengths that will cause two given characters to appear at the
    // same position in the generator string
    std::unordered_set<int> speclen;
    for (int i = 0; i < n; i++) {
        for (int j = i == 0 ? 0 : -m + 1; j < m; j++) {
            std::vector<long long> d = divisors((long long)i * W + j);
            for (auto x : d) {
                if (x <= W) {
                    speclen.insert(x);
                }
            }
        }
    }
    // A normal length l will yield SZ^(l-n*m) different generators
    // Sum is (SZ^(W-n*m+1)-1)/(SZ-1)
    int ans = (long long)(powermod(SZ, std::max(W, n * m - 1) - n * m + 1, MOD) - 1) * powermod(SZ - 1, MOD - 2, MOD) % MOD;
    // Deal with special lengths
    for (auto x : speclen) {
        if (x >= n * m) {
            ans = (ans - powermod(SZ, x - n * m, MOD) + MOD) % MOD;
        }
        bool ok = true;
        int cntdup = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int ni = i;
                int nj = j + x;
                while (ni < n && nj >= m) {
                    ni++;
                    nj = nj + (W - nj + x - 1) / x * x - W;
                }
                if (ni < n && nj < m) {
                    if (fragment[ni][nj] == fragment[i][j]) {
                        // This cell will not determine a new position
                        // in the generator string
                        cntdup++;
                    } else {
                        // Conflicting information
                        ok = false;
                        break;
                    }
                }
            }
            if (!ok) {
                break;
            }
        }
        if (ok) {
            ans = (ans + powermod(SZ, x - n * m + cntdup, MOD)) % MOD;
        }
    }
    return ans;
}

std::vector<long long> CharacterBoard::divisors(long long x)
{
    std::vector<long long> s;
    for (int i = 1; (long long)i * i <= x; i++) {
        if (x % i == 0) {
            s.push_back(i);
            if (i * i < x) {
                s.push_back(x / i);
            }
        }
    }
    return s;
}
