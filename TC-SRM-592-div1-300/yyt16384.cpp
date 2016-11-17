#include <string>

class LittleElephantAndBalls {
  public:
    int getNumber(std::string s);
};

int LittleElephantAndBalls::getNumber(std::string s)
{
    int ans = 0;
    int cr = 0;
    int cg = 0;
    int cb = 0;
    for (auto c : s) {
        // For every color, put the first ball in the left part and the
        // second ball in the right part
        ans += cr + cg + cb;
        if (c == 'R' && cr < 2) {
            cr++;
        } else if (c == 'G' && cg < 2) {
            cg++;
        } else if (c == 'B' && cb < 2) {
            cb++;
        }
    }
    return ans;
}
