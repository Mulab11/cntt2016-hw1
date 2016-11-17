#include <string>
#include <tuple>
#include <vector>

class CirclesGame {
  public:
    std::string whoCanWin(std::vector<int> x, std::vector<int> y, std::vector<int> r);

  private:
    bool isInside(std::tuple<int, int, int> a, std::tuple<int, int, int> b);
    int getSG(const std::vector<std::tuple<int, int, int>> a, std::tuple<int, int, int> x);
};

std::string CirclesGame::whoCanWin(std::vector<int> x, std::vector<int> y, std::vector<int> r)
{
    std::vector<std::tuple<int, int, int>> c(x.size());
    for (int i = 0; i < (int)x.size(); i++) {
        c[i] = std::make_tuple(x[i], y[i], r[i]);
    }
    int sg = 0;
    for (int i = 0; i < (int)x.size(); i++) {
        bool ok = true;
        for (int j = 0; j < (int)x.size(); j++) {
            if (isInside(c[i], c[j])) {
                ok = false;
                break;
            }
        }
        if (ok) {
            sg ^= getSG(c, c[i]);
        }
    }
    return sg ? "Alice" : "Bob";
}

bool CirclesGame::isInside(std::tuple<int, int, int> a, std::tuple<int, int, int> b)
{
    int dr = std::get<2>(a) - std::get<2>(b);
    if (dr >= 0) {
        return false;
    }
    int dx = std::get<0>(a) - std::get<0>(b);
    int dy = std::get<1>(a) - std::get<1>(b);
    return (long long)dx * dx + (long long)dy * dy < (long long)dr * dr;
}

int CirclesGame::getSG(const std::vector<std::tuple<int, int, int>> a, std::tuple<int, int, int> x)
{
    int s = 0;
    int t = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (isInside(a[i], x)) {
            bool ok = true;
            for (int j = 0; j < (int)a.size(); j++) {
                if (isInside(a[j], x) && isInside(a[i], a[j])) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                int p = getSG(a, a[i]);
                s ^= p;
                t |= p;
            }
        }
    }
    // Find the least significant bit x where no SG values of subtrees
    // have 1 on this bit
    int u = ~t & -~t;
    return (s & -u) | u;
}
