#include <string>
#include <vector>

class CheckerExpansion {
  public:
    std::vector<std::string> resultAfter(long long t, long long x0, long long y0, int w, int h);

  private:
    char getElement(long long t, long long x, long long y);
};

std::vector<std::string> CheckerExpansion::resultAfter(long long t, long long x0, long long y0, int w, int h)
{
    std::vector<std::string> ans(h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            ans[i] += getElement(t, x0 + j, y0 + h - i - 1);
        }
    }
    return ans;
}

char CheckerExpansion::getElement(long long t, long long x, long long y)
{
    if ((x + y) % 2) {
        // This cell will never contain any checkers
        return '.';
    }
    long long u = (x + y) / 2;
    long long v = y;
    if (u >= t) {
        // This checker has not been placed yet
        return '.';
    }
    // This cell contains a checker if C(u, v) is odd
    bool ok = (~u & v) == 0;
    char tp = u % 2 ? 'B' : 'A';
    return ok ? tp : '.';
}
