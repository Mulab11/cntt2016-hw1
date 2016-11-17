#include <algorithm>
#include <string>
#include <utility>
#include <vector>

static const int INF = 0x3f3f3f3f;

class MagicalHats {
  public:
    int findMaximumReward(std::vector<std::string> board, std::vector<int> coins, int numGuesses);

  private:
    std::vector<int> state2to3;

    int getStateID(int x, int y);
};

int MagicalHats::findMaximumReward(std::vector<std::string> board, std::vector<int> coins, int numGuesses)
{
    std::vector<std::pair<int, int>> pos;
    for (int i = 0; i < (int)board.size(); i++) {
        for (int j = 0; j < (int)board[0].length(); j++) {
            if (board[i][j] == 'H') {
                pos.push_back(std::make_pair(i, j));
            }
        }
    }
    int n = pos.size();
    std::vector<int> bitcnt(1 << n);
    bitcnt[0] = 0;
    for (int i = 1; i < (1 << n); i++) {
        bitcnt[i] = bitcnt[i & (i - 1)] + 1;
    }
    std::vector<char> stateok(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        if (n - bitcnt[i] != (int)coins.size()) {
            continue;
        }
        std::vector<char> xvis(board.size());
        std::vector<char> yvis(board[0].length());
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                xvis[pos[j].first] ^= true;
                yvis[pos[j].second] ^= true;
            }
        }
        bool ok = true;
        for (auto x : xvis) {
            if (x) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }
        for (auto x : yvis) {
            if (x) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }
        stateok[i] = true;
    }
    std::vector<int> pw3(n + 1);
    pw3[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw3[i] = pw3[i - 1] * 3;
    }
    state2to3.resize(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        int s = 0;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                s += pw3[j];
            }
        }
        state2to3[i] = s;
    }
    std::vector<int> f(pw3[n]);
    for (int i = 0; i < (1 << n); i++) {
        int u = ~i & ((1 << n) - 1);
        for (int j = u; j >= 0; j = j ? (j - 1) & u : -1) {
            if (i == 0 ? !stateok[j] : f[getStateID(i & (i - 1), j)] == INF && f[getStateID(i & (i - 1), j | (i & -i))] == INF) {
                f[getStateID(i, j)] = INF;
                continue;
            }
            int s = 0;
            if (n - bitcnt[i] < numGuesses) {
                // Enumerate the current guess
                int t = i;
                for (int p = t & -t; p > 0; t &= ~p, p = t & -t) {
                    // The magician can choose whether to put a coin in
                    // this hat
                    s = std::max(s, std::min(f[getStateID(i & ~p, j)] + 1, f[getStateID(i & ~p, j | p)]));
                }
            }
            f[getStateID(i, j)] = s;
        }
    }
    int anscnt = f[getStateID((1 << n) - 1, 0)];
    if (anscnt == INF) {
        return -1;
    }
    std::vector<int> c = coins;
    std::nth_element(c.begin(), c.begin() + anscnt, c.end());
    // The magician will give you coins with the smallest values
    int ans = 0;
    for (int i = 0; i < anscnt; i++) {
        ans += c[i];
    }
    return ans;
}

int MagicalHats::getStateID(int x, int y)
{
    return state2to3[x] * 2 + state2to3[y];
}
