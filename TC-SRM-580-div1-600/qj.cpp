#include <bits/stdc++.h>

using namespace std;

inline bool comp(const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) { return lhs.second < rhs.second; }

class ShoutterDiv1 {
  std::vector<int> s, t;
  std::vector< std::pair<int, int> > pool;
  int n;
  void bfs(std::vector<int> &res) {
    std::vector<int> q;
    for (int i = 0; i < n; ++i) if (res[i] == 0) q.push_back(i);
    for (int i = 0; i < q.size(); ++i) {
      int a = q[i];
      for (int j = 0; j < n; ++j) {
        if (res[j] == -1 && std::max(pool[j].first, pool[a].first) <= std::min(pool[j].second, pool[a].second)) {
          res[j] = res[a] + 1;
          q.push_back(j);
        }
      }
    }
  }
 public:
  int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1) {
    for (int i = 0; i < s1.size(); ++i) {
      for (int j = 0; j < s1[i].length(); ++j) {
        s.push_back(1000 * s1000[i][j] + 100 * s100[i][j] + 10 * s10[i][j] + s1[i][j] - 1111 * '0');
        t.push_back(1000 * t1000[i][j] + 100 * t100[i][j] + 10 * t10[i][j] + t1[i][j] - 1111 * '0');
      }
    }
    n = s.size();
    if (n == 1) return 0;
    for (int i = 0; i < n; ++i) pool.push_back(std::make_pair(s[i], t[i]));
    std::sort(pool.begin(), pool.end());
    std::vector<int> f(n, -1), g(n, -1);
    int l = 0, r = 0;
    for (int i = 0; i < n; ++i) if (pool[i].first > pool[r].first) r = i;
    for (int i = 0; i < n; ++i) if (pool[i].second < pool[l].second) l = i;
    // the message will be read by everyone iff the message is read by l and r
    f[l] = g[r] = 0;
    bfs(f);
    bfs(g);
    // get the distance between the i-th interval and l / r
    for (int i = 0; i < n; ++i) if (f[i] < 0 || g[i] < 0) return -1; // no solution if one of l and r is unreachable from i
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) ans[i] = std::max(f[i] - 1, 0) + std::max(g[i] - 1, 0); // calculate the minimal number of reposts necessary
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (pool[i].first <= pool[j].first && pool[j].second <= pool[i].second) ans[j] = std::min(ans[j], ans[i] + 1);
    // special case: the route from i to l and the route from i to r have common vertex
    return std::accumulate(ans.begin(), ans.end(), 0);
  }
};

// CUT begin
ifstream data("ShoutterDiv1.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1, int __expected) {
    time_t startClock = clock();
    ShoutterDiv1 *instance = new ShoutterDiv1();
    int __result = instance->count(s1000, s100, s10, s1, t1000, t100, t10, t1);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<string> s1000;
        from_stream(s1000);
        vector<string> s100;
        from_stream(s100);
        vector<string> s10;
        from_stream(s10);
        vector<string> s1;
        from_stream(s1);
        vector<string> t1000;
        from_stream(t1000);
        vector<string> t100;
        from_stream(t100);
        vector<string> t10;
        from_stream(t10);
        vector<string> t1;
        from_stream(t1);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s1000, s100, s10, s1, t1000, t100, t10, t1, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475743633;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "ShoutterDiv1 (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
