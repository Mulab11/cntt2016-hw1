#include <algorithm>
#include <string>
#include <vector>

class FlippingBitsDiv1 {
  public:
    int getmin(std::vector<std::string> S, int M);

  private:
    int getmin1(const std::string &s, int m);
    int getmin2(const std::string &s, int m);
};

int FlippingBitsDiv1::getmin(std::vector<std::string> S, int M)
{
    std::string str;
    for (const auto &x : S) {
        str += x;
    }
    int n = str.length();
    if (M < n / M) {
        return getmin1(str, M);
    } else {
        return getmin2(str, M);
    }
}

int FlippingBitsDiv1::getmin1(const std::string &s, int m)
{
    int ans = s.length();
    // Enumerate the values of ans[0..m-1]
    for (int i = 0; i < (1 << m); i++) {
        // Minimum number of operations needed for first k*m bits,
        // assuming the last m bits is flipped or not
        int f0 = 0;
        int f1 = 0;
        for (int j = 0; j <= (int)s.length(); j += m) {
            int s0 = 0;
            int s1 = 0;
            for (int k = j; k < j + m && k < (int)s.length(); k++) {
                if (s[k] - '0' == ((i >> (k % m)) & 1)) {
                    s1++;
                } else {
                    s0++;
                }
            }
            int g0 = std::min(f0, f1 + 1) + s0;
            int g1 = std::min(f0 + 1, f1) + s1;
            f0 = g0;
            f1 = g1;
        }
        ans = std::min(ans, f0);
    }
    return ans;
}

int FlippingBitsDiv1::getmin2(const std::string &s, int m)
{
    int l = s.length() / m;
    int ans = s.length();
    // Enumerate operation 2 used
    for (int i = 0; i < (1 << l); i++) {
        int sum = 0;
        for (int j = 0; j < l; j++) {
            if (((i >> j) & 1) != ((i >> (j + 1)) & 1)) {
                sum++;  // An operation 2 with first j*m bits needed
            }
        }
        for (int j = 0; j < m; j++) {
            int cnt0 = 0;
            int cnt1 = 0;
            for (int k = j; k < (int)s.length(); k += m) {
                int val = (s[k] - '0') ^ ((i >> (k / m)) & 1);
                if (val) {
                    cnt1++;
                } else {
                    cnt0++;
                }
            }
            // Change all 0 bits to 1, or all 1 bits to 0
            sum += std::min(cnt0, cnt1);
        }
        ans = std::min(ans, sum);
    }
    return ans;
}
