#include <array>
#include <string>

class FoxAndHandle {
  public:
    std::string lexSmallestName(std::string S);

  private:
    static const int SZ = 26;
};

std::string FoxAndHandle::lexSmallestName(std::string S)
{
    std::array<int, SZ> cnt = {0};
    for (auto x : S) {
        cnt[x - 'a']++;
    }
    std::array<int, SZ> anscnt = {0};
    std::string ans;
    int startpos = 0;
    for (int i = 0; i < (int)S.length() / 2; i++) {
        int r = SZ;
        int rpos = -1;
        std::array<int, SZ> prefixcnt = {0};
        for (int j = 0; j < (int)S.length(); j++) {
            if (j >= startpos && anscnt[S[j] - 'a'] < cnt[S[j] - 'a'] / 2) {
                bool ok = true;
                // Can append S[j] to answer if all characters before S[j]
                // can be part of the permutation part
                for (int k = 0; k < SZ; k++) {
                    if (prefixcnt[k] - anscnt[k] > cnt[k] / 2) {
                        ok = false;
                        break;
                    }
                }
                if (ok && S[j] - 'a' < r) {
                    r = S[j] - 'a';
                    rpos = j;
                }
            }
            prefixcnt[S[j] - 'a']++;
        }
        anscnt[r]++;
        ans += r + 'a';
        startpos = rpos + 1;
    }
    return ans;
}
