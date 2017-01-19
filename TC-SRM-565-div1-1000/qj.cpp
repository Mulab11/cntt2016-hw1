#include <bits/stdc++.h>

using namespace std;

typedef long long i64;
typedef std::pair<int, int> Info;

class UnknownTree {
  static const int N = 50 + 10, MOD = 1000000009;
  inline void add(int &lhs, i64 rhs) { lhs = (lhs + rhs) % MOD; }
  int count(std::vector<int> d) {
    // distance to root
    std::sort(d.begin(), d.end());
    int res = 1;
    for (int i = 0, j = 0; i < d.size(); ++i) {
      while (d[j] < d[i]) ++j;
      res = res * (j + 1LL) % MOD;
    }
    return res;
  }
  int count2(std::vector<Info> d) {
    // distance to two vertices
    const int n = d.size();
    std::sort(d.begin(), d.end());
    if (n > 1 && d[0].first == d[1].first) return 0;
    int a = 0;
    while (d[a].second) ++a;
    if (a == 0) {
      std::vector<int> X;
      for (int i = 1; i < n; ++i) if (d[i].first - d[0].first == d[i].second) X.push_back(d[i].second); else return 0;
      return count(X);
    }
    std::vector<int> X;
    std::vector<Info> A;
    for (int i = 1; i < n; ++i) {
      int detX = d[i].first - d[0].first, detA = d[i].second - d[0].second;
      if (detX == detA) X.push_back(detX); else if (d[i].second + detX >= d[0].second) A.push_back(d[i]); else return 0;
    }
    return (i64)count(X) * count2(A) % MOD;
  }
  int solveY(const std::vector<int> &a, const std::vector<int> &b, const std::vector<int> &c, int x) {
    const int n = a.size();
    // Y-shape case
    // the intersection of path A-B, A-C, and B-C is x
    std::vector<int> X;
    std::vector<Info> A, B, C;
    A.push_back(std::make_pair(a[x], 0));
    A.push_back(std::make_pair(0, a[x]));
    B.push_back(std::make_pair(b[x], 0));
    B.push_back(std::make_pair(0, b[x]));
    C.push_back(std::make_pair(c[x], 0));
    C.push_back(std::make_pair(0, c[x]));
    for (int i = 0; i < n; ++i) {
      if (i == x) continue;
      int detA = a[i] - a[x], detB = b[i] - b[x], detC = c[i] - c[x];
      if (detA > 0 && detA == detB && detB == detC) { // i is a successor of x
        X.push_back(detA);
      } else if (detA > 0 && detA == detB) {
        C.push_back(std::make_pair(detA, c[i]));
      } else if (detA > 0 && detA == detC) {
        B.push_back(std::make_pair(detA, b[i]));
      } else if (detB > 0 && detB == detC) {
        A.push_back(std::make_pair(detB, a[i]));
      } else { // illegal
        return 0;
      }
    }
    int res = count(X);
    res = (i64)res * count2(A) % MOD;
    res = (i64)res * count2(B) % MOD;
    res = (i64)res * count2(C) % MOD;
    return res;
  }
  int chain(const std::vector<int> &a, const std::vector<int> &b, const std::vector<int> &c) {
    // chain A - B - C
    std::set<Info> info; // all the possible pairs of (dist(A, B), dist(B, C))
    const int n = a.size();
    for (int i = 0; i < n; ++i) {
      // i is a successor of A
      int x = b[i] - a[i], y = c[i] - b[i];
      if (x > 0 && y > 0) info.insert(std::make_pair(x, y));
      // i is in between A and B
      x = a[i] + b[i], y = c[i] - b[i];
      if (x > 0 && y > 0) info.insert(std::make_pair(x, y));
      // i is a successor of B
      x = a[i] - b[i], y = c[i] - b[i];
      if (x > 0 && y > 0) info.insert(std::make_pair(x, y));
      // i is in between B and C
      x = a[i] - b[i], y = b[i] + c[i];
      if (x > 0 && y > 0) info.insert(std::make_pair(x, y));
      // i is a successor of C
      x = a[i] - b[i], y = b[i] - c[i];
      if (x > 0 && y > 0) info.insert(std::make_pair(x, y));
    }
    int res = 0;
    for (std::set<Info>::iterator it = info.begin(); it != info.end(); ++it) {
      const int distAB = it->first, distBC = it->second;
      std::vector<int> B;
      std::vector<Info> A, C;
      A.push_back(std::make_pair(0, distAB));
      A.push_back(std::make_pair(distAB, 0));
      C.push_back(std::make_pair(0, distBC));
      C.push_back(std::make_pair(distBC, 0));
      bool flag = true;
      for (int i = 0; i < n; ++i) {
        if (a[i] == b[i] + distAB && c[i] == b[i] + distBC) {
          B.push_back(b[i]);
        } else if (c[i] == b[i] + distBC) {
          A.push_back(std::make_pair(b[i], a[i]));
        } else if (a[i] == b[i] + distAB) {
          C.push_back(std::make_pair(b[i], c[i]));
        } else {
          flag = false;
          break;
        }
      }
      if (flag) add(res, (i64)count2(A) * count(B) % MOD * count2(C));
    }
    return res;
  }
 public:
  int getCount(vector<int> a, vector<int> b, vector<int> c) {
    int res = 0;
    add(res, chain(a, b, c));
    add(res, chain(a, c, b));
    add(res, chain(b, a, c));
    for (int i = 0; i < a.size(); ++i) add(res, solveY(a, b, c, i));
    return res;
  }
};
