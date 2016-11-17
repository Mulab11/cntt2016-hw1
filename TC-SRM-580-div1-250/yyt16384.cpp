#include <algorithm>
#include <tuple>
#include <vector>

class EelAndRabbit {
  public:
    int getmax(std::vector<int> l, std::vector<int> t);
};

int EelAndRabbit::getmax(std::vector<int> l, std::vector<int> t)
{
    std::vector<std::tuple<int, bool, int>> c(2 * l.size());
    for (int i = 0; i < (int)l.size(); i++) {
        c[2 * i] = std::make_tuple(t[i], false, i);
        c[2 * i + 1] = std::make_tuple(t[i] + l[i], true, i);
    }
    std::sort(c.begin(), c.end());
    std::vector<std::vector<char>> a(c.size() + 1, std::vector<char>(l.size()));
    // Get set of available eels at each event point
    for (int i = 0; i < (int)c.size(); i++) {
        a[i + 1] = a[i];
        a[i + 1][std::get<2>(c[i])] = !std::get<1>(c[i]);
    }
    int ans = 0;
    // Enumerate the two instants
    for (int i = 0; i <= (int)c.size(); i++) {
        for (int j = i + 1; j <= (int)c.size(); j++) {
            int cnt = 0;
            for (int k = 0; k < (int)l.size(); k++) {
                if (a[i][k] || a[j][k]) {
                    cnt++;
                }
            }
            ans = std::max(ans, cnt);
        }
    }
    return ans;
}
