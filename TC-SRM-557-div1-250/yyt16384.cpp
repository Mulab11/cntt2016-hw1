#include <algorithm>
#include <string>

class FoxAndMountainEasy {
  public:
    std::string possible(int n, int h0, int hn, std::string history);
};

std::string FoxAndMountainEasy::possible(int n, int h0, int hn, std::string history)
{
    if ((h0 + hn + n) % 2) {
        return "NO";
    }
    int cntup = (hn - h0 + n) / 2;
    int cntdown = n - cntup;
    int hsup = 0;
    int hsdown = 0;
    int hsdec = 0;
    for (auto x : history) {
        if (x == 'U') {
            hsup++;
        } else {
            hsdown++;
        }
        hsdec = std::max(hsdec, hsdown - hsup);
    }
    // Needs enough number of up and down moves, and it should be
    // possible to get enough height to process history with
    // non-negative heights
    if (hsup <= cntup && hsdown <= cntdown && h0 + cntup - hsup >= hsdec) {
        return "YES";
    } else {
        return "NO";
    }
}
