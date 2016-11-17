#include <array>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

class LeftRightDigitsGame2 {
  public:
    std::string minNumber(std::string digits, std::string lowerBound);
};

std::string LeftRightDigitsGame2::minNumber(std::string digits, std::string lowerBound)
{
    int n = digits.size();
    // f[i][j] = minimum number constructed with current digits that has
    // i digits in the beginning, and j represents whether the prefix
    // part is = or > lowerBound, and whether the suffix part is >= or <
    // lowerBound
    std::vector<std::array<std::tuple<bool, std::string, std::string>, 3>> f(n + 1);
    f[0][1] = std::make_tuple(true, "", "");
    for (int i = 0; i < n; i++) {
        std::vector<std::array<std::tuple<bool, std::string, std::string>, 3>> g(n + 1);
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k < 3; k++) {
                if (std::get<0>(f[j][k])) {
                    int nextk;
                    std::tuple<bool, std::string, std::string> nextval;
                    // Place the next digit in the left part
                    if (k == 2) {
                        nextk = 2;
                    } else if (digits[n - i - 1] < lowerBound[j]) {
                        nextk = -1;
                    } else if (digits[n - i - 1] > lowerBound[j]) {
                        nextk = 2;
                    } else {
                        nextk = k;
                    }
                    if (nextk != -1) {
                        nextval = std::make_tuple(true, std::get<1>(f[j][k]) + digits[n - i - 1], std::get<2>(f[j][k]));
                        if (!std::get<0>(g[j + 1][nextk]) || nextval < g[j + 1][nextk]) {
                            g[j + 1][nextk] = nextval;
                        }
                    }
                    // Place the next digit in the right part
                    if (k == 2) {
                        nextk = 2;
                    } else if (digits[n - i - 1] < lowerBound[n - i + j - 1]) {
                        nextk = 0;
                    } else if (digits[n - i - 1] > lowerBound[n - i + j - 1]) {
                        nextk = 1;
                    } else {
                        nextk = k;
                    }
                    nextval = std::make_tuple(true, std::get<1>(f[j][k]), digits[n - i - 1] + std::get<2>(f[j][k]));
                    if (!std::get<0>(g[j][nextk]) || nextval < g[j][nextk]) {
                        g[j][nextk] = nextval;
                    }
                }
            }
        }
        f = std::move(g);
    }
    std::string ans;
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= 2; j++) {
            if (std::get<0>(f[i][j])) {
                std::string s = std::get<1>(f[i][j]) + std::get<2>(f[i][j]);
                if (ans.empty() || s < ans) {
                    ans = s;
                }
            }
        }
    }
    return ans;
}
