#include <string>
#include <vector>

class SurveillanceSystem {
  public:
    std::string getContainerInfo(std::string containers, std::vector<int> reports, int L);
};

std::string SurveillanceSystem::getContainerInfo(std::string containers, std::vector<int> reports, int L)
{
    int n = containers.size();
    std::vector<int> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + (containers[i] == 'X');
    }
    std::vector<int> vtot(L + 1);
    std::vector<std::vector<int>> vcov(L + 1, std::vector<int>(n));
    for (int i = 0; i <= n - L; i++) {
        int x = sum[i + L] - sum[i];
        vtot[x]++;
        for (int j = i; j < i + L; j++) {
            vcov[x][j]++;
        }
    }
    std::vector<int> vcnt(L + 1);
    for (auto x : reports) {
        vcnt[x]++;
    }
    std::vector<char> pm1(n);
    std::vector<char> pm0(n, true);
    for (int i = 0; i <= L; i++) {
        for (int j = 0; j < n; j++) {
            // If there is at least one camera watching this cell and at
            // least one camera has this result, this cell may be
            // monitored
            if (vcnt[i] > 0 && vcov[i][j]) {
                pm1[j] = true;
            }
            // If there are not enough segments that don't cover this
            // cell, it will always be monitored
            if (vtot[i] - vcov[i][j] < vcnt[i]) {
                pm0[j] = false;
            }
        }
    }
    std::string ans;
    for (int i = 0; i < n; i++) {
        if (!pm1[i]) {
            ans += '-';
        } else if (!pm0[i]) {
            ans += '+';
        } else {
            ans += '?';
        }
    }
    return ans;
}
