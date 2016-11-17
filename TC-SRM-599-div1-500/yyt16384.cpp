#include <algorithm>
#include <cmath>
#include <tuple>
#include <vector>

class FindPolygons {
  public:
    double minimumPolygon(int L);

  private:
    int optimalTriangle(int L);
    std::vector<std::tuple<int, int, int>> pythagoreanTriples(int maxlen);
};

double FindPolygons::minimumPolygon(int L)
{
    // Every edge needs to have integer length, and perimeter of the
    // polygon must be even, because for every Pythagorean triple (a, b,
    // c) there is (a + b + c) % 2 == 0
    if (L == 2 || L % 2) {
        return -1;
    }
    // The optimal polygon must be either a triangle or a rectangle
    int x = optimalTriangle(L);
    if (x != -1) {
        return x;
    } else {
        return L / 2 % 2;
    }
}

int FindPolygons::optimalTriangle(int L)
{
    int ans = L + 1;
    // Every edge must be shorter than L / 2 to satisfy the triangle
    // inequality
    int maxlen = (L - 1) / 2;
    std::vector<std::tuple<int, int, int>> s = pythagoreanTriples(maxlen);
    // Assume a vertex is in the lower-left corner, and enumerate the
    // two edges connected to it
    for (auto x = s.crbegin(); x != s.crend(); x++) {
        int a1 = std::get<0>(*x);
        int b1 = std::get<1>(*x);
        int c1 = std::get<2>(*x);
        for (auto y = s.crbegin(); y != x && L - c1 - std::get<2>(*y) <= maxlen; y++) {
            int a2 = std::get<0>(*y);
            int b2 = std::get<1>(*y);
            int c2 = std::get<2>(*y);
            int c3 = L - c1 - c2;
            if ((a1 - a2) * (a1 - a2) + (b1 - b2) * (b1 - b2) == c3 * c3 ||
                    (a1 - b2) * (a1 - b2) + (b1 - a2) * (b1 - a2) == c3 * c3) {
                int diff = std::max({c1, c2, c3}) - std::min({c1, c2, c3});
                ans = std::min(ans, diff);
            }
        }
    }
    return ans > L ? -1 : ans;
}

std::vector<std::tuple<int, int, int>> FindPolygons::pythagoreanTriples(int maxlen)
{
    std::vector<std::tuple<int, int, int>> s;
    for (int i = 1; i <= maxlen; i++) {
        for (int j = 0; 2 * j * j < i * i; j++) {
            int rem = i * i - j * j;
            int k = std::sqrt(rem) + 0.5;
            if (k * k == rem) {
                s.push_back(std::make_tuple(j, k, i));
            }
        }
    }
    return s;
}
