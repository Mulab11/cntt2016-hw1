#include <algorithm>
#include <string>
#include <vector>

static const int INF = 0x3f3f3f3f;

class ShoutterDiv1 {
  public:
    int count(std::vector<std::string> s1000, std::vector<std::string> s100, std::vector<std::string> s10, std::vector<std::string> s1, std::vector<std::string> t1000, std::vector<std::string> t100, std::vector<std::string> t10, std::vector<std::string> t1);

  private:
    int countWork(const std::vector<int> &s, const std::vector<int> &t);
};

int ShoutterDiv1::count(std::vector<std::string> s1000, std::vector<std::string> s100, std::vector<std::string> s10, std::vector<std::string> s1, std::vector<std::string> t1000, std::vector<std::string> t100, std::vector<std::string> t10, std::vector<std::string> t1)
{
    std::string strs1000;
    for (const auto &x : s1000) {
        strs1000 += x;
    }
    std::string strs100;
    for (const auto &x : s100) {
        strs100 += x;
    }
    std::string strs10;
    for (const auto &x : s10) {
        strs10 += x;
    }
    std::string strs1;
    for (const auto &x : s1) {
        strs1 += x;
    }
    std::vector<int> s(strs1000.length());
    for (int i = 0; i < (int)strs1000.length(); i++) {
        s[i] = (strs1000[i] - '0') * 1000 + (strs100[i] - '0') * 100 + (strs10[i] - '0') * 10 + strs1[i] - '0';
    }
    std::string strt1000;
    for (const auto &x : t1000) {
        strt1000 += x;
    }
    std::string strt100;
    for (const auto &x : t100) {
        strt100 += x;
    }
    std::string strt10;
    for (const auto &x : t10) {
        strt10 += x;
    }
    std::string strt1;
    for (const auto &x : t1) {
        strt1 += x;
    }
    std::vector<int> t(strt1000.length());
    for (int i = 0; i < (int)strt1000.length(); i++) {
        t[i] = (strt1000[i] - '0') * 1000 + (strt100[i] - '0') * 100 + (strt10[i] - '0') * 10 + strt1[i] - '0';
    }
    return countWork(s, t);
}

int ShoutterDiv1::countWork(const std::vector<int> &s, const std::vector<int> &t)
{
    int n = s.size();
    std::vector<int> rs(2 * n);
    for (int i = 0; i < n; i++) {
        rs[2 * i] = s[i];
        rs[2 * i + 1] = t[i];
    }
    std::sort(rs.begin(), rs.end());
    rs.erase(std::unique(rs.begin(), rs.end()), rs.end());
    std::vector<int> left(n);
    std::vector<int> right(n);
    for (int i = 0; i < n; i++) {
        left[i] = std::lower_bound(rs.begin(), rs.end(), s[i]) - rs.begin();
        right[i] = std::lower_bound(rs.begin(), rs.end(), t[i]) - rs.begin();
    }
    int maxl = -INF;
    int minr = INF;
    for (int i = 0; i < n; i++) {
        maxl = std::max(maxl, left[i]);
        minr = std::min(minr, right[i]);
    }
    // fr[i] = minimum cost to extend right boundary to cover all
    // elements starting at position i
    std::vector<int> fr(rs.size(), INF);
    for (int i = rs.size() - 1; i >= 0; i--) {
        if (i >= maxl) {
            // Already covering all elements
            fr[i] = 0;
            continue;
        }
        for (int j = 0; j < n; j++) {
            if (left[j] <= i && right[j] > i) {
                // Try to extend with segment j
                fr[i] = std::min(fr[i], fr[right[j]] + 1);
            }
        }
    }
    // fl[i] = minimum cost to extend left boundary to cover all
    // elements starting at position i
    std::vector<int> fl(rs.size(), INF);
    for (int i = 0; i < (int)rs.size(); i++) {
        if (i <= minr) {
            // Already covering all elements
            fl[i] = 0;
            continue;
        }
        for (int j = 0; j < n; j++) {
            if (right[j] >= i && left[j] < i) {
                // Try to extend with segment j
                fl[i] = std::min(fl[i], fl[left[j]] + 1);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int u = fl[left[i]] + fr[right[i]];
        for (int j = 0; j < n; j++) {
            if (left[j] <= left[i] && right[j] >= right[i]) {
                // May choose a segment that completely covers i. This
                // will happen only in the first turn.
                u = std::min(u, fl[left[j]] + fr[right[j]] + 1);
            }
        }
        if (u >= INF) {
            return -1;
        }
        ans += u;
    }
    return ans;
}
