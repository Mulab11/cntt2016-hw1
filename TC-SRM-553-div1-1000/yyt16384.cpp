#include <algorithm>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;

class DirectedGraph {
  public:
    int n = 0;
    std::vector<std::vector<std::tuple<int, int, int>>> edge;
    std::vector<std::unordered_map<int, long long>> dist;

    DirectedGraph() { }
    DirectedGraph(int n_) : n(n_), edge(n), dist(n) { }

    void addEdge(int x, int y, int w1, int w2);
    void work(int s);
};

void DirectedGraph::addEdge(int x, int y, int w1, int w2)
{
    edge[x].push_back(std::make_tuple(y, w1, w2));
}

void DirectedGraph::work(int s)
{
    for (auto &x : dist) {
        x.clear();
    }
    dist[s][0] = 0;
    for (int i = 0; i < n; i++) {
        std::vector<std::unordered_map<int, long long>> dist2 = dist;
        for (int x = 0; x < n; x++) {
            for (auto p : dist[x]) {
                for (auto e : edge[x]) {
                    int y = std::get<0>(e);
                    int next1 = p.first + std::get<1>(e);
                    long long next2 = p.second + std::get<2>(e);
                    auto it = dist2[y].find(next1);
                    if (it == dist2[y].end()) {
                        dist2[y][next1] = next2;
                    } else {
                        it->second = std::min(it->second, next2);
                    }
                }
            }
        }
        dist = std::move(dist2);
    }
}

class YamanoteLine {
  public:
    long long howMany(int n, std::vector<int> s1, std::vector<int> t1, std::vector<int> l1, std::vector<int> s2, std::vector<int> t2, std::vector<int> l2);

  private:
    long long divide(long long x, int y);
};

long long YamanoteLine::howMany(int n, std::vector<int> s1, std::vector<int> t1, std::vector<int> l1, std::vector<int> s2, std::vector<int> t2, std::vector<int> l2)
{
    DirectedGraph g(n);
    for (int i = 0; i < n - 1; i++) {
        g.addEdge(i + 1, i, 0, -1);
    }
    g.addEdge(0, n - 1, 1, -1);
    for (int i = 0; i < (int)s1.size(); i++) {
        if (s1[i] < t1[i]) {
            g.addEdge(t1[i], s1[i], 0, -l1[i]);
        } else {
            g.addEdge(t1[i], s1[i], 1, -l1[i]);
        }
    }
    for (int i = 0; i < (int)s2.size(); i++) {
        if (s2[i] < t2[i]) {
            g.addEdge(s2[i], t2[i], 0, l2[i]);
        } else {
            g.addEdge(s2[i], t2[i], -1, l2[i]);
        }
    }
    long long l = 0;
    long long r = INFLL;
    for (int i = 0; i < n; i++) {
        g.work(i);
        for (auto p : g.dist[i]) {
            // This cycle should have non-negative weight
            if (p.first > 0) {
                l = std::max(l, divide(-p.second + p.first - 1, p.first));
            } else if (p.first < 0) {
                r = std::min(r, divide(p.second, -p.first));
            } else {
                if (p.second < 0) {
                    return 0;
                }
            }
        }
    }
    return r == INFLL ? -1 : std::max<long long>(r - l + 1, 0);
}

long long YamanoteLine::divide(long long x, int y)
{
    return x / y - (x % y < 0);
}
