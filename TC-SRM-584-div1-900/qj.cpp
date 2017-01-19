#include <bits/stdc++.h>

using namespace std;

const int N = 100, INF = 0x3f3f3f3f;

class FoxTheLinguist {
  int dist[1 << 10][N + 1];
  std::vector< std::pair<int, int> > adj[N + 1];
  inline int pos(char x, char y) { return (x - 'A') * 10 + y - '0'; }
  void parse(const std::vector<std::string> &text) {
    std::string t;
    for (int i = 0; i < text.size(); ++i) t += text[i];
    std::stringstream ss(t);
    for (std::string s; ss >> s;) {
      char x1, y1, x2, y2;
      int z;
      sscanf(s.c_str(), " %c %c-> %c %c:%d", &x1, &y1, &x2, &y2, &z);
      adj[pos(x2, y2)].push_back(std::make_pair(pos(x1, y1), z));
    }
  }
  inline void check(int &lhs, int rhs) { if (rhs < lhs) lhs = rhs; }
 public:
  int minimalHours(int n, vector<string> _s) {
    parse(_s);
    memset(dist, 0x3f, sizeof dist);
    for (int i = 0; i < n; ++i) dist[1 << i][pos('A' + i, '9')] = 0;
    for (int i = 0; i < n; ++i) adj[pos('A' + i, '0')].push_back(std::make_pair(N, 0));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < 9; ++j)
        adj[pos('A' + i, '0' + j)].push_back(std::make_pair(pos('A' + i, '0' + j + 1), 0));
    for (int s = 0; s < (1 << n); ++s) {
      // Steiner Tree
      // f[s][i] : we are at vertex i, the set of target vertex that we can reach is s
      static std::pair<int, int> heap[10 * N * N];
      int top = 0;
      for (int i = 0; i <= N; ++i) if (dist[s][i] < INF) heap[top++] = std::make_pair(-dist[s][i], i);
      for (std::make_heap(heap, heap + top); top;) {
        // bellman-ford
        std::pop_heap(heap, heap + top);
        std::pair<int, int> cur = heap[--top];
        int a = cur.second;
        if (-cur.first > dist[s][a]) continue;
        for (int i = 0; i < adj[a].size(); ++i) {
          int b = adj[a][i].first, c = adj[a][i].second;
          if (dist[s][a] + c < dist[s][b]) {
            heap[top++] = std::make_pair(-(dist[s][b] = dist[s][a] + c), b);
            std::push_heap(heap, heap + top);
          }
        }
      }
      for (int i = 0; i <= N; ++i)
        for (int t = 0; t < (1 << n); ++t)
          check(dist[s | t][i], dist[s][i] + dist[t][i]); // update the answer
    }
    int res = dist[(1 << n) - 1][N];
    return res == INF ? -1 : res;
  }
};
