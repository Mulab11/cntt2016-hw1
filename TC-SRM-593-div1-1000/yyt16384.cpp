#include <string>
#include <utility>
#include <vector>

class WolfDelaymasterHard {
  public:
    int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd);

  private:
    static const int MOD = 1000000007;

    std::string generateString(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd);
};

int WolfDelaymasterHard::countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
{
    std::string s = generateString(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
    int m = N / 2;
    // Range of right end with only '?' character in the 'w'-part
    std::vector<int> maxposr(m + 1);
    maxposr[m] = m;
    // Maximum right-end of '?'-only string starting from current
    // character
    int maxpos_empty = N;
    // Maximum right-end of string without 'w' starting from current
    // character
    int maxpos_o = N;
    for (int i = N - 1; i >= 0; i--) {
        if (s[i] == 'w') {
            maxpos_empty = i;
            maxpos_o = i;
        } else if (s[i] == 'o') {
            maxpos_empty = i;
        }
        if (i % 2 == 0) {
            int x = i / 2;
            maxposr[x] = std::min(2 * maxpos_empty - i, maxpos_o) / 2;
        }
    }
    // Range of left end with at least one 'w' character in the 'w'-part
    std::vector<std::pair<int, int>> rangel(m + 1);
    // Range of left end of 'o'-part that contains the most possible
    // 'o's
    int pos_ol = -1;
    int pos_or = 0;
    // Range of left end of 'w'-part that contains at least one 'w'
    int pos_wl = -1;
    int pos_wr = -1;
    int pos_pre_o = -1;
    for (int i = 1; i <= N; i++) {
        if (s[i - 1] == 'w') {
            pos_ol = i - 1;
            pos_or = i;
            pos_wl = pos_pre_o;
            pos_wr = i - 1;
        } else if (s[i - 1] == 'o') {
            pos_pre_o = i - 1;
        } else {
            if (pos_or == i - 1) {
                // Right half is currently '?'-only
                pos_or = i;
            }
        }
        if (i % 2 == 0) {
            int x = i / 2;
            int pos_prel = std::max(pos_wl, 2 * pos_ol - i + 1);
            int pos_prer = std::min(pos_wr, 2 * pos_or - i);
            pos_prel = (pos_prel >= 0 ? pos_prel / 2 : (pos_prel - 1) / 2);
            pos_prer = (pos_prer >= 0 ? pos_prer / 2 : (pos_prer - 1) / 2);
            pos_prer = std::max(pos_prer, pos_prel);
            rangel[x] = std::make_pair(pos_prel, pos_prer);
        }
    }
    // f[i] = number of different valid words obtained from first 2 * i
    // characters
    std::vector<int> f(m + 1);
    std::vector<int> fs(m + 1);
    std::vector<int> ftoadd(m + 1);
    f[0] = 1;
    fs[0] = 1;
    ftoadd[1] = 1;
    ftoadd[maxposr[0] + 1] = (ftoadd[maxposr[0] + 1] + MOD - 1) % MOD;
    for (int i = 1; i <= m; i++) {
        // The 'w'-part has at least one 'w'
        int t = ((rangel[i].second >= 0 ? fs[rangel[i].second] : 0) - (rangel[i].first >= 0 ? fs[rangel[i].first] : 0) + MOD) % MOD;
        f[i] = (f[i] + t) % MOD;
        // The 'w'-part has only '?'s
        ftoadd[i] = (ftoadd[i] + ftoadd[i - 1]) % MOD;
        f[i] = (f[i] + ftoadd[i]) % MOD;
        fs[i] = (fs[i - 1] + f[i]) % MOD;
        if (i < m) {
            ftoadd[i + 1] = (ftoadd[i + 1] + f[i]) % MOD;
        }
        if (maxposr[i] < m) {
            ftoadd[maxposr[i] + 1] = (ftoadd[maxposr[i] + 1] - f[i] + MOD) % MOD;
        }
    }
    return f[m];
}

std::string WolfDelaymasterHard::generateString(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)
{
    std::string s(N, '?');
    int x;
    x = w0;
    for (int i = 0; i < wlen; i++) {
        s[x] = 'w';
        x = ((long long)x * wmul + wadd) % N;
    }
    x = o0;
    for (int i = 0; i < olen; i++) {
        s[x] = 'o';
        x = ((long long)x * omul + oadd) % N;
    }
    return s;
}
