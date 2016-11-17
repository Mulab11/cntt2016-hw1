#include <algorithm>
#include <vector>

class RockPaperScissors {
  public:
    double bestScore(std::vector<int> rockProb, std::vector<int> paperProb, std::vector<int> scissorsProb);
};

double RockPaperScissors::bestScore(std::vector<int> rockProb, std::vector<int> paperProb, std::vector<int> scissorsProb)
{
    int n = rockProb.size();
    std::vector<double> pr(n);
    std::vector<double> pp(n);
    std::vector<double> ps(n);
    for (int i = 0; i < n; i++) {
        pr[i] = rockProb[i] / 300.0;
        pp[i] = paperProb[i] / 300.0;
        ps[i] = scissorsProb[i] / 300.0;
    }
    std::vector<std::vector<std::vector<double>>> fpelem(n + 1);
    for (int i = 0; i <= n; i++) {
        fpelem[i].resize(n - i + 1);
        for (int j = 0; j <= n - i; j++) {
            fpelem[i][j].resize(n - i - j + 1);
        }
    }
    // f[u][i][j][k] = probability of getting i rocks, j papers and k
    // scissors after i+j+k steps without choosing dice u
    std::vector<std::vector<std::vector<std::vector<double>>>> fp(n, fpelem);
    for (int u = 0; u < n; u++) {
        std::vector<std::vector<std::vector<double>>> &f = fp[u];
        f[0][0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int r = i; r >= 0; r--) {
                for (int p = i - r; p >= 0; p--) {
                    for (int s = i - r - p; s >= 0; s--) {
                        double pchosen = (double)(r + p + s + 1) / (i + 1);
                        if (i != u) {
                            f[r + 1][p][s] += f[r][p][s] * pchosen * pr[i];
                            f[r][p + 1][s] += f[r][p][s] * pchosen * pp[i];
                            f[r][p][s + 1] += f[r][p][s] * pchosen * ps[i];
                        }
                        f[r][p][s] *= 1 - (double)(r + p + s) / (i + 1);
                    }
                }
            }
        }
    }
    double ans = 0;
    for (int r = 0; r < n; r++) {
        for (int p = 0; p < n - r; p++) {
            for (int s = 0; s < n - r - p; s++) {
                // Consider the state (r, p, s)
                // Probability of next die giving rock/paper/scissors
                double pnextr = 0;
                double pnextp = 0;
                double pnexts = 0;
                // Enumerate the next die
                for (int i = 0; i < n; i++) {
                    pnextr += fp[i][r][p][s] / (n - r - p - s) * pr[i];
                    pnextp += fp[i][r][p][s] / (n - r - p - s) * pp[i];
                    pnexts += fp[i][r][p][s] / (n - r - p - s) * ps[i];
                }
                // Use the optimal strategy
                ans += std::max({3 * pnextr + pnextp, 3 * pnextp + pnexts, 3 * pnexts + pnextr});
            }
        }
    }
    return ans;
}
