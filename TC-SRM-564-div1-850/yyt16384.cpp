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

class DefectiveAddition {
  public:
    int count(std::vector<int> cards, int n);

  private:
    static const int MOD = 1000000007;
    static const int MAXBITS = 30;
};

int DefectiveAddition::count(std::vector<int> cards, int n)
{
    int ans = 0;
    for (int i = MAXBITS - 1; i >= 0; i--) {
        int cnt0 = 1;
        int cnt1 = 0;
        int allxorcnt = 1;
        bool allxor = false;
        for (int j = 0; j < (int)cards.size(); j++) {
            int s = (cards[j] & ((1 << i) - 1)) + 1;
            if ((cards[j] >> i) & 1) {
                int ncnt0 = ((long long)cnt0 * (1 << i) + (long long)cnt1 * s) % MOD;
                int ncnt1 = ((long long)cnt1 * (1 << i) + (long long)cnt0 * s) % MOD;
                cnt0 = ncnt0;
                cnt1 = ncnt1;
                allxorcnt = (long long)allxorcnt * s % MOD;
                allxor ^= true;
            } else {
                cnt0 = (long long)cnt0 * s % MOD;
                cnt1 = (long long)cnt1 * s % MOD;
                allxorcnt = (long long)allxorcnt * s % MOD;
            }
        }
        int cnt = (n >> i) & 1 ? cnt1 : cnt0;
        if (i == 0) {
            // No remaining bits to consider
            ans = (ans + cnt) % MOD;
        } else if (allxor == ((n >> i) & 1)) {
            // One choice need to be considered later
            ans = (ans + (long long)(cnt - allxorcnt + MOD) * powermod(1 << i, MOD - 2, MOD)) % MOD;
        } else {
            // In any valid choice, there is at least one unlimited
            // value, so exactly half of the choices are valid answers
            ans = (ans + (long long)cnt * powermod(1 << i, MOD - 2, MOD)) % MOD;
            break;
        }
    }
    return ans;
}
