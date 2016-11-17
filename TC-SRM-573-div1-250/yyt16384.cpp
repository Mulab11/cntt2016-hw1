#include <algorithm>
#include <vector>

class TeamContest {
  public:
    int worstRank(std::vector<int> strength);
};

int TeamContest::worstRank(std::vector<int> strength)
{
    int selfstr = std::max({strength[0], strength[1], strength[2]}) + std::min({strength[0], strength[1], strength[2]});
    std::vector<int> a(strength.begin() + 3, strength.end());
    std::sort(a.begin(), a.end());
    int cur = 0;
    int ans = 1;
    // Match the smallest possible elements greedily
    for (int i = a.size() - 1; i > cur + 1; i--) {
        while (cur + 1 < i && a[i] + a[cur] <= selfstr) {
            cur++;
        }
        if (cur + 1 == i) {
            break;
        }
        ans++;
        cur += 2;
    }
    return ans;
}
