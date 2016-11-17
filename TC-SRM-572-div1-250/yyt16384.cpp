#include <algorithm>
#include <array>
#include <string>

class NewArenaPassword {
  public:
    int minChange(std::string oldPassword, int K);

  private:
    static const int SZ = 26;
};

int NewArenaPassword::minChange(std::string oldPassword, int K)
{
    int n = oldPassword.length();
    int ans = 0;
    // There should be s[i] = s[i + n - K] in the result string s
    for (int i = 0; i < n - K; i++) {
        std::array<int, SZ> cnt = {0};
        for (int j = i; j < n; j += n - K) {
            cnt[oldPassword[j] - 'a']++;
        }
        // Change all other kinds of characters into this one
        int p = std::max_element(cnt.begin(), cnt.end()) - cnt.begin();
        for (int j = 0; j < SZ; j++) {
            if (j != p) {
                ans += cnt[j];
            }
        }
    }
    return ans;
}
