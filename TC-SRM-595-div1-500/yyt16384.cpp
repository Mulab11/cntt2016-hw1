#include <algorithm>
#include <string>
#include <vector>

class LittleElephantAndRGB {
  public:
    long long getNumber(std::vector<std::string> list, int minGreen);
};

long long LittleElephantAndRGB::getNumber(std::vector<std::string> list, int minGreen)
{
    std::string s;
    for (const auto &x : list) {
        s += x;
    }
    int n = s.length();
    std::vector<int> presuflen(n);
    std::vector<int> preoklen(n);
    for (int i = 0; i < n; i++) {
        presuflen[i] = s[i] == 'G' ? (i ? presuflen[i - 1] : 0) + 1 : 0;
        preoklen[i] = presuflen[i] >= minGreen ? i - minGreen + 1 : (i ? preoklen[i - 1] : -1);
    }
    std::vector<int> sufprelen(n);
    std::vector<int> sufoklen(n);
    for (int i = n - 1; i >= 0; i--) {
        sufprelen[i] = s[i] == 'G' ? (i < n - 1 ? sufprelen[i + 1] : 0) + 1 : 0;
        sufoklen[i] = sufprelen[i] >= minGreen ? i + minGreen - 1 : (i < n - 1 ? sufoklen[i + 1] : n);
    }
    long long ans = 0;
    // Enumerate b and c
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int reml = i - preoklen[i];
            int remr = sufoklen[j] - j;
            // Either S[a..b] or S[c..d] is nice
            ans += (i + 1) * (n - j) - reml * remr;
            int maxsufl = std::min(presuflen[i], reml);
            int maxprer = std::min(sufprelen[j], remr);
            if (maxsufl + maxprer < minGreen) {
                continue;
            }
            // b - a + 1 > maxsufl and d - c + 1 > maxprer
            ans += (reml - maxsufl) * (remr - maxprer);
            // b - a + 1 > maxsufl and d - c + 1 <= maxprer
            ans += (reml - maxsufl) * (maxprer - (minGreen - maxsufl) + 1);
            // b - a + 1 <= maxsufl and d - c + 1 > maxprer
            ans += (maxsufl - (minGreen - maxprer) + 1) * (remr - maxprer);
            // b - a + 1 <= maxsufl and d - c + 1 <= maxprer
            int t = maxsufl + maxprer - minGreen + 1;
            ans += t * (t + 1) / 2;
        }
    }
    return ans;
}
