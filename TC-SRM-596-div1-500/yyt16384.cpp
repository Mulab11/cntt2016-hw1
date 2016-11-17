#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

class BitwiseAnd {
  public:
    std::vector<long long> lexSmallest(std::vector<long long> subset, int N);

  private:
    static const int MAXBITS = 60;

    std::vector<int> getBits(long long x);
};

std::vector<long long> BitwiseAnd::lexSmallest(std::vector<long long> subset, int N)
{
    // Ensure elements are positive and distinct
    if (N == 1 && subset.empty()) {
        return {1};
    }
    if (N == 2 && subset.empty()) {
        return {1, 2};
    }
    if (N == 2 && subset.size() == 1) {
        int x = subset[0];
        if (x == 1) {
            return {1, 2};
        } else if (!(x & (x - 1))) {
            return {x, x | 1};
        }
    }
    for (auto x : subset) {
        for (auto y : subset) {
            if (!(x & y)) {
                return {};
            }
        }
    }
    std::vector<std::vector<int>> a;
    a.reserve(subset.size());
    for (auto x : subset) {
        a.push_back(getBits(x));
    }
    std::unordered_map<int, std::vector<int>> bitpos;
    for (int i = 0; i < (int)a.size(); i++) {
        for (auto x : a[i]) {
            bitpos[x].push_back(i);
        }
    }
    // The bits that are only in one number can be used in remaining
    // numbers
    std::vector<std::vector<int>> pos1;
    pos1.reserve(N);
    pos1.resize(subset.size());
    for (const auto &x : bitpos) {
        if (x.second.size() >= 3) {
            return {};
        }
        if (x.second.size() == 1) {
            pos1[x.second[0]].push_back(x.first);
        }
    }
    for (auto &x : pos1) {
        std::sort(x.begin(), x.end());
        if ((int)x.size() < N - (int)subset.size()) {
            // Not enough bits for matching with remaining numbers
            return {};
        }
        // Extra bits will not be used
        x.resize(N - subset.size());
    }
    std::vector<long long> ans = subset;
    int start = 0;
    for (int i = subset.size(); i < N; i++) {
        // Choose the smallest possible number
        long long x = 0;
        for (auto &p : pos1) {
            x |= 1LL << p[0];
            p.erase(p.begin());
        }
        std::vector<int> s;
        for (int j = 0; j < N - i - 1; j++) {
            int p = start;
            while (p < MAXBITS && bitpos.find(p) != bitpos.end()) {
                p++;
            }
            if (p == MAXBITS) {
                return {};
            }
            s.push_back(p);
            x |= 1LL << p;
            start = p + 1;
        }
        pos1.push_back(std::move(s));
        ans.push_back(x);
    }
    std::sort(ans.begin(), ans.end());
    return ans;
}

std::vector<int> BitwiseAnd::getBits(long long x)
{
    std::vector<int> bits;
    int cur = 0;
    while (x) {
        if (x % 2) {
            bits.push_back(cur);
        }
        x /= 2;
        cur++;
    }
    return bits;
}
