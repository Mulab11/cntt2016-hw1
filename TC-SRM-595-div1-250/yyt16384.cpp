#include <vector>

class LittleElephantAndIntervalsDiv1 {
  public:
    long long getNumber(int M, std::vector<int> L, std::vector<int> R);
};

long long LittleElephantAndIntervalsDiv1::getNumber(int M, std::vector<int> L, std::vector<int> R)
{
    // Every stage with at least one ball visible in the end multiplies
    // the answer by 2
    std::vector<int> col(M, -1);
    for (int i = 0; i < (int)L.size(); i++) {
        int l = L[i] - 1;
        int r = R[i] - 1;
        for (int j = l; j <= r; j++) {
            col[j] = i;
        }
    }
    std::vector<char> vis(L.size());
    for (auto x : col) {
        if (x != -1) {
            vis[x] = true;
        }
    }
    int cnt = 0;
    for (auto x : vis) {
        if (x) {
            cnt++;
        }
    }
    return 1LL << cnt;
}
