#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>

typedef std::complex<double> Complex;

const double PI = acos(-1.), eps = 1e-7;

class SplittingFoxes2 {
  int n;
  inline Complex eval(const std::vector<Complex> &poly, const Complex &x) {
    // calculate poly(x)
    Complex cur(1.), res(0.);
    for (int i = 0; i < poly.size(); ++i, cur *= x) res += poly[i] * cur;
    return res;
  }
  std::vector<Complex> dft(const std::vector<Complex> &a, int sig = 1) {
    // sig = 1: dft
    // sig = -1: idft
    std::vector<Complex> res(n);
    for (int i = 0; i < n; ++i) {
      double arg = sig * 2. * PI * i / n;
      res[i] = eval(a, Complex(cos(arg), sin(arg)));
    }
    if (sig < 0) for (int i = 0; i < n; ++i) res[i] /= n;
    return res;
  }
  std::vector<int> sqr(const std::vector<int> &poly) {
    // calculate the square of a polynomial
    std::vector<int> res(poly.size());
    for (int i = 0; i < poly.size(); ++i)
      for (int j = 0; j < poly.size(); ++j)
        res[(i + j) % poly.size()] += poly[i] * poly[j];
    return res;
  }
 public:
  std::vector<int> getPattern(const std::vector<int> &a) {
    std::vector<Complex> val(n = a.size());
    std::copy(a.begin(), a.end(), val.begin());
    val = dft(val);
    for (int i = 0; i < val.size(); ++i) val[i] = sqrt(val[i]);
    int k = n / 2;
    std::vector<int> ans(n);
    ans[0] = 1e9;
    for (int s = 0; s < (1 << (k + 1)); ++s) {
      std::vector<Complex> temp(n);
      for (int j = 0; j <= k; ++j) if (s >> j & 1) temp[j] = temp[(n - j) % n] = val[j]; else temp[j] = temp[(n - j) % n] = -val[j];
      temp = dft(temp, -1);
      std::vector<int> cur(n);
      for (int j = 0; j < n; ++j) cur[j] = temp[j].real() + .4; // weird precision issue.. + 0.5 will get WA
      if (sqr(cur) == a && *std::min_element(cur.begin(), cur.end()) >= 0 && std::lexicographical_compare(cur.begin(), cur.end(), ans.begin(), ans.end())) ans = cur; // verify the answer & update answer
    }
    return ans[0] == 1e9 ? std::vector<int>(1, -1) : ans;
  }
};
