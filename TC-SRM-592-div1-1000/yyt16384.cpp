#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>

const double PI = std::acos(-1);

class SplittingFoxes2 {
  public:
    std::vector<int> getPattern(std::vector<int> amount);

  private:
    std::vector<std::complex<double>> DFT(const std::vector<std::complex<double>> &a, bool inverse);
    bool checkAnswer(const std::vector<int> &x, const std::vector<int> &y);
};

std::vector<int> SplittingFoxes2::getPattern(std::vector<int> amount)
{
    int n = amount.size();
    std::vector<std::complex<double>> a(amount.begin(), amount.end());
    a = DFT(a, false);
    std::vector<std::complex<double>> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = std::sqrt(a[i]);
    }
    std::vector<int> ans = {-1};
    // Enumerate which square roots to use
    for (int i = 0; i < (1 << (n / 2 + 1)); i++) {
        std::vector<std::complex<double>> c = b;
        for (int j = 0; j < n; j++) {
            if ((i >> std::min(j, n - j)) & 1) {
                c[j] = -c[j];
            }
        }
        c = DFT(c, true);
        std::vector<int> d(n);
        for (int j = 0; j < n; j++) {
            d[j] = c[std::min(j, n - j)].real() / n + 0.5;
        }
        if (checkAnswer(d, amount) && (ans[0] == -1 || d < ans)) {
            ans = d;
        }
    }
    return ans;
}

std::vector<std::complex<double>> SplittingFoxes2::DFT(const std::vector<std::complex<double>> &a, bool inverse)
{
    int n = a.size();
    std::complex<double> w = std::polar(1.0, inverse ? -2 * PI / n : 2 * PI / n);
    std::complex<double> x = 1;
    std::vector<std::complex<double>> c(n);
    for (int i = 0; i < n; i++) {
        std::complex<double> s = 1;
        for (int j = 0; j < n; j++) {
            c[i] += s * a[j];
            s *= x;
        }
        x *= w;
    }
    return c;
}

bool SplittingFoxes2::checkAnswer(const std::vector<int> &x, const std::vector<int> &y)
{
    int n = x.size();
    for (auto p : x) {
        if (p < 0) {
            return false;
        }
    }
    std::vector<int> s(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s[(i + j) % n] += x[i] * x[j];
        }
    }
    return s == y;
}
