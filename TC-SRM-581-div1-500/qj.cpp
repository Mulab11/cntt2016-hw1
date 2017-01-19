#include <bits/stdc++.h>

using namespace std;

int n, k;

class Tree {
  static const int N = 300 + 10;
  std::vector<int> adj[N], res;
  void dfs(int a, int fa = -1, int dep = 1) {
    if (dep <= k) ++res[dep];
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i];
      if (b != fa) dfs(b, a, dep + 1);
    }
  }
 public:
  Tree() {}
  Tree(const std::vector<std::string> &t) {
    std::vector<int> temp;
    std::string s;
    for (int i = 0; i < t.size(); ++i) s += t[i];
    std::stringstream ss(s);
    for (int x; ss >> x;) temp.push_back(x);
    n = temp.size() + 1;
    for (int i = 0; i < n; ++i) adj[i].clear();
    for (int i = 1; i < n; ++i) adj[temp[i - 1]].push_back(i), adj[i].push_back(temp[i - 1]);
  }
  std::vector<int> solve() {
    res.clear();
    res.resize(k + 1);
    for (int i = 0; i < n; ++i) dfs(i);
    return res;
  }
};

class TreeUnion {
  Tree tree[2];
 public:
  double expectedCycles(vector<string> tree0, vector<string> tree1, int _k) {
    // since k <= 7 and every vertex is adjacent to exactly one vertex in the other tree
    // every path must be: a_0 -> b_0 -> c_0 -> a_1 -> b_1 -> c_1 -> d_1 -> a_0
    // so we simply calculate the number of paths of which the length is in [2, 5]
    k = _k;
    tree[0] = Tree(tree0);
    tree[1] = Tree(tree1);
    std::vector<int> a = tree[0].solve(), b = tree[1].solve();
    double res = 0.;
    for (int i = 2; i <= k - 2; ++i) res += (double)a[i] * b[k - i]; // convolution
    return res / 2 / n / (n - 1);
  }
};
