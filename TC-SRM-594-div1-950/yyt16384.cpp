#include <algorithm>
#include <unordered_map>

class FoxAndAvatar {
  public:
    int minimalSteps(int n, int width, int x);

  private:
    bool isOneStep(int n, int width, int x);
    std::unordered_map<int, int> getTrans(int n, int width, int x);
};

int FoxAndAvatar::minimalSteps(int n, int width, int x)
{
    if (n == 1) {
        return 0;
    }
    if (isOneStep(n, width, x - 1)) {
        return 1;
    }
    std::unordered_map<int, int> trans = getTrans(n, width, x - 1);
    for (auto p : trans) {
        if (isOneStep(p.second, width, p.first)) {
            return 2;
        }
    }
    for (auto p : trans) {
        std::unordered_map<int, int> trans2 = getTrans(p.second, width, p.first);
        for (auto q : trans2) {
            if (isOneStep(q.second, width, q.first)) {
                return 3;
            }
        }
    }
    // It is always possible to solve in <= 4 steps
    return 4;
}

bool FoxAndAvatar::isOneStep(int n, int width, int x)
{
    return (x >= width) + (x < n - width) + (x % width > 0) + (x % width < width - 1 && x < n - 1) == 1;
}

std::unordered_map<int, int> FoxAndAvatar::getTrans(int n, int width, int x)
{
    int p = x / width;
    int q = x % width;
    int h = n / width - p;
    int nrem = n % width;
    std::unordered_map<int, int> trans;
    trans[x] = (p + 1) * width;
    // Enumerate the size of deleted items before x
    for (int i = 1; i <= p + 1; i++) {
        for (int j = 1; j <= (i == p + 1 ? q : width); j++) {
            int delbelow;  // Maximum number of deleted items after x
            if (i <= p && j < width - q) {
                int extralen = std::min(j, std::max(nrem - q - 1, 0));
                delbelow = j * h + extralen;
            } else if (j <= q) {
                int extralen = std::min(j, nrem);
                delbelow = j * (h - 1) + extralen;
            } else {
                delbelow = 0;
            }
            int nextx = x - i * j;
            int nextn = n - i * j - delbelow;
            if (trans.find(nextx) == trans.end()) {
                trans[nextx] = nextn;
            } else {
                // Smaller n is better
                trans[nextx] = std::min(trans[nextx], nextn);
            }
        }
    }
    return trans;
}
