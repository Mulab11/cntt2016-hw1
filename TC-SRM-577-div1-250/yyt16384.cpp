#include <algorithm>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

class EllysRoomAssignmentsDiv1 {
  public:
    double getAverage(std::vector<std::string> ratings);

  private:
    static const int ROOMCNTDIV = 20;
};

double EllysRoomAssignmentsDiv1::getAverage(std::vector<std::string> ratings)
{
    std::string s;
    for (const auto &x : ratings) {
        s += x;
    }
    std::vector<int> a;
    std::istringstream ss(s);
    int x;
    while (ss >> x) {
        a.push_back(x);
    }
    int n = a.size();
    int selfrating = a[0];
    std::sort(a.begin(), a.end(), std::greater<int>());
    int selfpos = std::lower_bound(a.begin(), a.end(), selfrating, std::greater<int>()) - a.begin();
    int roomcnt = (n + ROOMCNTDIV - 1) / ROOMCNTDIV;
    int pc = n / roomcnt;
    int sum = 0;
    for (int i = 0; i < pc * roomcnt; i++) {
        if (i / roomcnt != selfpos / roomcnt) {
            sum += a[i];
        }
    }
    // Each of these people will be in Elly's room with probability
    // 1/roomcnt
    double u = (double)sum / roomcnt + selfrating;
    if (selfpos < pc * roomcnt) {
        int sumrem = 0;
        for (int i = pc * roomcnt; i < n; i++) {
            sumrem += a[i];
        }
        double pextra = (double)(n % roomcnt) / roomcnt;
        double ans1 = (u * pextra + (double)sumrem / roomcnt) / (pc + 1);
        double ans2 = u * (1 - pextra) / pc;
        return ans1 + ans2;
    } else {
        return u / (pc + 1);
    }
}
