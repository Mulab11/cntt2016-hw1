#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

class Ear {
  public:
    long long getCount(std::vector<std::string> redX, std::vector<std::string> blueX, std::vector<std::string> blueY);

  private:
    int divide(int x, int y);
};

long long Ear::getCount(std::vector<std::string> redX, std::vector<std::string> blueX, std::vector<std::string> blueY)
{
    std::string srx;
    for (const auto &x : redX) {
        srx += x;
    }
    std::string sbx;
    for (const auto &x : blueX) {
        sbx += x;
    }
    std::string sby;
    for (const auto &x : blueY) {
        sby += x;
    }
    int val;
    std::vector<int> rx;
    std::istringstream ssrx(srx);
    while (ssrx >> val) {
        rx.push_back(val);
    }
    std::vector<int> bx;
    std::istringstream ssbx(sbx);
    while (ssbx >> val) {
        bx.push_back(val);
    }
    std::vector<int> by;
    std::istringstream ssby(sby);
    while (ssby >> val) {
        by.push_back(val);
    }
    std::vector<int> c = rx;
    std::sort(c.begin(), c.end());
    long long ans = 0;
    // Enumerate P
    for (int i = 0; i < (int)bx.size(); i++) {
        // Enumerate Q
        for (int j = 0; j < (int)bx.size(); j++) {
            if (by[i] > by[j]) {
                int pn = bx[j] * by[i] - bx[i] * by[j];
                int pd = by[i] - by[j];
                // A and D must be on different sides of PQ
                int liml = divide(pn + pd - 1, pd);
                int limr = divide(pn + pd, pd);
                int lima = std::min(liml, bx[i]);
                int limb = bx[j];
                int limc = bx[j] + 1;
                int limd = std::max(limr, bx[i] + 1);
                int cnta = std::lower_bound(c.begin(), c.end(), lima) - c.begin();
                int cntb = std::lower_bound(c.begin(), c.end(), limb) - c.begin();
                int cntc = c.end() - std::lower_bound(c.begin(), c.end(), limc);
                int cntd = c.end() - std::lower_bound(c.begin(), c.end(), limd);
                int u = (2 * cntb - cnta - 1) * cnta / 2;
                int v = (2 * cntc - cntd - 1) * cntd / 2;
                ans += (long long)u * v;
            }
        }
    }
    return ans;
}

int Ear::divide(int x, int y)
{
    return x / y - (x % y < 0);
}
