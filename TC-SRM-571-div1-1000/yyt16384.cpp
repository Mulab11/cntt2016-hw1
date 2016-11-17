#include <algorithm>
#include <cmath>
#include <string>
#include <tuple>
#include <vector>

class CandyOnDisk {
  public:
    std::string ableToAchieve(std::vector<int> x, std::vector<int> y, std::vector<int> r, int sx, int sy, int tx, int ty);
};

std::string CandyOnDisk::ableToAchieve(std::vector<int> x, std::vector<int> y, std::vector<int> r, int sx, int sy, int tx, int ty)
{
    if (tx == sx && ty == sy) {
        return "YES";
    }
    int n = x.size();
    // Process the special case separately to avoid precision issues
    for (int i = 0; i < n; i++) {
        long long ds2 = (long long)(sx - x[i]) * (sx - x[i]) + (long long)(sy - y[i]) * (sy - y[i]);
        long long dt2 = (long long)(tx - x[i]) * (tx - x[i]) + (long long)(ty - y[i]) * (ty - y[i]);
        if (ds2 <= (long long)r[i] * r[i] && ds2 == dt2) {
            return "YES";
        }
    }
    // c[i] = (candy can be on disk i, minimum distance from center,
    // maximum distance from center)
    std::vector<std::tuple<bool, double, double>> c(n);
    for (int i = 0; i < n; i++) {
        double d = std::hypot(sx - x[i], sy - y[i]);
        if (d <= r[i]) {
            c[i] = std::make_tuple(true, d, d);
        }
    }
    std::vector<std::vector<char>> vis(n, std::vector<char>(n));
    for (int i = 0; i < n * n; i++) {
        for (int j = 0; j < n; j++) {
            if (std::get<0>(c[j])) {
                double dl = std::get<1>(c[j]);
                double dr = std::get<2>(c[j]);
                for (int k = 0; k < n; k++) {
                    if (x[k] == x[j] && y[k] == y[j]) {
                        continue;
                    }
                    if (vis[j][k]) {
                        continue;
                    }
                    double djk = std::hypot(x[k] - x[j], y[k] - y[j]);
                    if (dr >= djk - r[k] && dl <= djk + r[k]) {
                        vis[j][k] = true;
                        // Move between disk j and disk k
                        double ndl = std::max<double>(djk - r[j], 0);
                        double ndr = std::min<double>(djk + r[j], r[k]);
                        if (std::get<0>(c[k])) {
                            std::get<1>(c[k]) = std::min(std::get<1>(c[k]), ndl);
                            std::get<2>(c[k]) = std::max(std::get<2>(c[k]), ndr);
                        } else {
                            c[k] = std::make_tuple(true, ndl, ndr);
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        bool ok = false;
        for (int j = 0; j < n; j++) {
            if (vis[j][i]) {
                ok = true;
                break;
            }
        }
        // Skip if only one disk is used to avoid precision issues
        if (std::get<0>(c[i]) && ok) {
            double d = std::hypot(tx - x[i], ty - y[i]);
            if (d >= std::get<1>(c[i]) && d <= std::get<2>(c[i])) {
                return "YES";
            }
        }
    }
    return "NO";
}
