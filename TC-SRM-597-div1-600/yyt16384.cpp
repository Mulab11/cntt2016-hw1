#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class ConvexPolygonGame {
  public:
    std::string winner(std::vector<int> X, std::vector<int> Y);

  private:
    std::unordered_map<int, std::pair<int, int>> getPointsInsidePolygon(const std::vector<int> &X, const std::vector<int> &Y);
    int divide(long long x, int y);
};

std::string ConvexPolygonGame::winner(std::vector<int> X, std::vector<int> Y)
{
    std::unordered_map<int, std::pair<int, int>> bounds = getPointsInsidePolygon(X, Y);
    // Either the first player can't make a move and lose, or she can
    // choose the triangle with minimum area and win
    // The first player can make a move if and only if there are three
    // points that are not collinear
    int x1;
    int y1;
    bool ok1 = false;
    int x2;
    int y2;
    bool ok2 = false;
    for (auto p : bounds) {
        int y = p.first;
        int xl = p.second.first;
        int xr = p.second.second;
        if (xr - xl >= 1) {
            if (ok1) {
                return "Masha";
            }
            x1 = xl;
            y1 = y;
            ok1 = true;
            x2 = xl + 1;
            y2 = y;
            ok2 = true;
        } else if (xl == xr) {
            if (!ok1) {
                x1 = xl;
                y1 = y;
                ok1 = true;
            } else if (!ok2) {
                x2 = xl;
                y2 = y;
                ok2 = true;
            } else {
                int x3 = xl;
                int y3 = y;
                if ((long long)(x2 - x1) * (y3 - y1) - (long long)(x3 - x1) * (y2 - y1) != 0) {
                    return "Masha";
                }
            }
        }
    }
    return "Petya";
}

std::unordered_map<int, std::pair<int, int>> ConvexPolygonGame::getPointsInsidePolygon(const std::vector<int> &X, const std::vector<int> &Y)
{
    int n = X.size();
    // Stores the left and right bounds of grid points inside the
    // polygon for each y coordinate
    std::unordered_map<int, std::pair<int, int>> bounds;
    for (int i = 0; i < n; i++) {
        int x1 = X[i];
        int y1 = Y[i];
        int x2 = X[(i + 1) % n];
        int y2 = Y[(i + 1) % n];
        if (y1 < y2) {
            // Current edge is in the right part of the polygon
            for (int y = y1; y <= y2; y++) {
                int x = divide((long long)(y - y1) * (x2 - x1) - (y == y1 || y == y2), y2 - y1) + x1;
                bounds[y].second = x;
            }
        } else if (y1 > y2) {
            // Current edge is in the left part of the polygon
            for (int y = y1; y >= y2; y--) {
                int x = divide((long long)(y - y2) * (x1 - x2) - (y != y1 && y != y2), y1 - y2) + x2 + 1;
                bounds[y].first = x;
            }
        } else {
            // Current edge is either the top edge or the bottom edge of
            // the polygon
            bounds[y1] = std::make_pair(std::min(x1, x2) + 1, std::max(x1, x2) - 1);
        }
    }
    return bounds;
}

int ConvexPolygonGame::divide(long long x, int y)
{
    return x / y - (x % y < 0);
}
