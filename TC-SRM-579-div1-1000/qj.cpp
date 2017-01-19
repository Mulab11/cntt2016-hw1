#include <cstring>
#include <vector>

const int N = 50 + 1;

class RockPaperScissors {
  int n;
  double f[N][N][N][N];
 public:
  double bestScore(std::vector<int> a, std::vector<int> b, std::vector<int> c) {
    memset(f, 0, sizeof f);
    n = a.size();
    // calculate the probabilities
    for (int i = 0; i < n; ++i) {
      f[i][0][0][0] = 1.;
      for (int j = 0; j < n; ++j) {
        for (int m = j + 1; m >= 0; --m) {
          for (int r = 0; r <= m; ++r) {
            for (int p = 0; r + p <= m; ++p) {
              int s = m - r - p;
              double q = m / (j + 1.);
              f[i][r][p][s] *= 1. - q;
              if (j != i) {
                double sum = 0.;
                if (r) sum += a[j] / 300. * f[i][r - 1][p][s];
                if (p) sum += b[j] / 300. * f[i][r][p - 1][s];
                if (s) sum += c[j] / 300. * f[i][r][p][s - 1];
                f[i][r][p][s] += q * sum;
              }
            }
          }
        }
      }
    }
    double res = 0.;
    for (int r = 0; r < n; ++r) {
      for (int p = 0; r + p < n; ++p) {
        for (int s = 0; r + p + s < n; ++s) {
          double x = 0., y = 0., z = 0.;
          for (int i = 0; i < n; ++i) {
            double t = f[i][r][p][s] / (n - r - p - s);
            x += a[i] / 300. * t;
            y += b[i] / 300. * t;
            z += c[i] / 300. * t;
          }
          res += std::max(std::max(3. * x + y, 3. * y + z), 3. * z + x);
        }
      }
    }
    return res;
  }
};
