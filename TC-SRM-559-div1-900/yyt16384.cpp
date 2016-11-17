#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

const double PI = std::acos(-1);

class CircusTents {
  public:
    double findMaximumDistance(std::vector<int> x, std::vector<int> y, std::vector<int> r);
};

double CircusTents::findMaximumDistance(std::vector<int> x, std::vector<int> y, std::vector<int> r)
{
    int n = x.size();
    std::vector<double> di(n);
    std::vector<double> tp(n);
    std::vector<double> tl(n);
    std::vector<double> cc(n);
    for (int i = 1; i < n; i++) {
        // Find the tangent points
        int d2 = (x[i] - x[0]) * (x[i] - x[0]) + (y[i] - y[0]) * (y[i] - y[0]);
        di[i] = std::sqrt(d2);
        double cosp = r[0] / di[i];
        tp[i] = std::acos(cosp);
        tl[i] = std::sqrt(d2 - r[0] * r[0]);
        cc[i] = std::fmod(std::atan2(y[i] - y[0], x[i] - x[0]) + 2 * PI, 2 * PI);
    }
    double ll = 0;
    double rr = 1e5;
    while (ll + 1e-9 < rr) {
        double mid = (ll + rr) / 2;
        std::vector<std::pair<double, int>> ev = {{0, 0}};
        int fullcov = 0;
        for (int i = 1; i < n; i++) {
            // Find the points with distance mid to this circle
            double dc = mid + r[i];
            double p;
            if (dc < di[i] - r[0]) {
                continue;
            }
            if (dc < tl[i]) {
                double cosp = (r[0] * r[0] + di[i] * di[i] - dc * dc) / (2 * r[0] * di[i]);
                cosp = std::min<double>(std::max<double>(cosp, 0), 1);
                p = std::acos(cosp);
            } else {
                p = tp[i] + (dc - tl[i]) / r[0];
            }
            // Points in this interval are not allowed
            if (p >= PI) {
                fullcov++;
            } else {
                double pl = std::fmod(cc[i] - p + 2 * PI, 2 * PI);
                double pr = std::fmod(cc[i] + p, 2 * PI);
                ev.push_back(std::make_pair(pl, 1));
                ev.push_back(std::make_pair(pr, -1));
                if (pl > pr) {
                    fullcov++;
                }
            }
        }
        std::sort(ev.begin(), ev.end());
        bool ok = false;
        int sum = fullcov;
        for (auto p : ev) {
            if (!sum) {
                ok = true;
                break;
            }
            sum += p.second;
        }
        if (ok) {
            ll = mid;
        } else {
            rr = mid;
        }
    }
    return (ll + rr) / 2;
}
