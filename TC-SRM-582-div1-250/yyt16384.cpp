#include <algorithm>
#include <utility>
#include <vector>

class SpaceWarDiv1 {
  public:
    long long minimalFatigue(std::vector<int> magicalGirlStrength, std::vector<int> enemyStrength, std::vector<long long> enemyCount);

  private:
    bool checkFatigue(long long p, const std::vector<int> &a, const std::vector<std::pair<int, long long>> &b);
};

long long SpaceWarDiv1::minimalFatigue(std::vector<int> magicalGirlStrength, std::vector<int> enemyStrength, std::vector<long long> enemyCount)
{
    std::vector<int> a = magicalGirlStrength;
    std::sort(a.begin(), a.end());
    std::vector<std::pair<int, long long>> b(enemyStrength.size());
    for (int i = 0; i < (int)enemyStrength.size(); i++) {
        b[i] = std::make_pair(enemyStrength[i], enemyCount[i]);
    }
    std::sort(b.begin(), b.end());
    if (a.back() < b.back().first) {
        return -1;
    }
    long long sum = 0;
    for (auto x : enemyCount) {
        sum += x;
    }
    // Binary search on the answer
    long long l = 0;
    long long r = sum;
    while (l + 1 < r) {
        long long mid = (l + r) >> 1;
        if (checkFatigue(mid, a, b)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}

bool SpaceWarDiv1::checkFatigue(long long p, const std::vector<int> &a, const std::vector<std::pair<int, long long>> &b)
{
    int curbpos = 0;
    long long curbcnt = 0;
    for (auto x : a) {
        long long s = 0;
        // Match enemies greedily
        while (curbpos < (int)b.size() && b[curbpos].first <= x && s < p) {
            long long u = std::min(p - s, b[curbpos].second - curbcnt);
            s += u;
            curbcnt += u;
            if (curbcnt == b[curbpos].second) {
                curbpos++;
                curbcnt = 0;
            }
        }
    }
    return curbpos == (int)b.size();
}
