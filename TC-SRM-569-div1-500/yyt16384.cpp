#include <algorithm>
#include <vector>

class TheJediTest {
  public:
    int minimumSupervisors(std::vector<int> students, int K);
};

int TheJediTest::minimumSupervisors(std::vector<int> students, int K)
{
    int ans = 0;
    int prevreq = 0;
    int curadd = 0;
    for (auto x : students) {
        int now = x + curadd;
        int selfcnt = x;
        // Move to previous floor
        int u = std::min(selfcnt, prevreq);
        now -= u;
        selfcnt -= u;
        ans += now / K;
        int rem = now % K;
        if (rem <= selfcnt) {
            // Remaining children can move to next floor
            prevreq = 0;
            curadd = rem;
        } else {
            // Not enough children for moving, maybe move some children
            // to this floor from the next floor
            ans++;
            prevreq = K - rem;
            curadd = 0;
        }
    }
    if (curadd) {
        // Cannot move right from the last floor
        ans++;
    }
    return ans;
}
