#include <algorithm>
#include <string>
#include <vector>

static const int INF = 0x3f3f3f3f;

class YetAnotherBoardGame {
  public:
    int minimumMoves(std::vector<std::string> board);

  private:
    int m;
    std::vector<int> a;
    std::vector<int> bitcnt;

    void initBitsetInfo(int n);
    int recurse(int x, int coltype, int coltypedet, int lastval, int lastops);
};

int YetAnotherBoardGame::minimumMoves(std::vector<std::string> board)
{
    int n = board.size();
    m = board[0].length();
    a.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'W') {
                a[i] |= 1 << j;
            }
        }
    }
    initBitsetInfo(m);
    int ans = INF;
    // Enumerate operations in first row
    for (int i = 0; i < (1 << m); i++) {
        for (int tp = 0; tp < 2; tp++) {
            int curval = a[0] ^ (i >> 1) ^ ((i << 1) & ((1 << m) - 1)) ^ (tp * i);
            ans = std::min(ans, recurse(1, tp * i, i, curval, i) + bitcnt[i]);
        }
    }
    return ans == INF ? -1 : ans;
}

void YetAnotherBoardGame::initBitsetInfo(int n)
{
    bitcnt.resize(1 << n);
    bitcnt[0] = 0;
    for (int i = 1; i < (1 << n); i++) {
        bitcnt[i] = bitcnt[i & (i - 1)] + 1;
    }
}

int YetAnotherBoardGame::recurse(int x, int coltype, int coltypedet, int lastval, int lastops)
{
    if (x == (int)a.size()) {
        if (lastval == 0) {
            return 0;
        }
        return INF;
    }
    int curcoldet = coltypedet & lastval;
    bool is1 = (~coltype & curcoldet) != 0;
    bool is2 = (coltype & curcoldet) != 0;
    int ans = INF;
    if (!is2) {
        // Use move type 1 for current row
        int curval = a[x] ^ lastops ^ (lastval >> 1) ^ ((lastval << 1) & ((1 << m) - 1));
        ans = std::min(ans, recurse(x + 1, coltype, coltypedet | lastval, curval, lastval) + bitcnt[lastval]);
    }
    if (!is1) {
        // Use move type 2 for current row
        int curval = a[x] ^ lastops ^ (lastval >> 1) ^ ((lastval << 1) & ((1 << m) - 1)) ^ lastval;
        ans = std::min(ans, recurse(x + 1, coltype | lastval, coltypedet | lastval, curval, lastval) + bitcnt[lastval]);
    }
    return ans;
}
