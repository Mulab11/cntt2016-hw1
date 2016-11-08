#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 10, INF = 0x3f3f3f3f;

class WallGameDiv1 {
  int n, m, a[N][N], sum[N][N], f[N][N][N][2];
  int solve(int x, int l, int r, int s) {
    if (x == n - 1) return a[x][l];
    int &res = f[x][l][r][s];
    if (res < INF) return res;
    int p = s ? r : l; // The current position of the token is (x, p).
    res = a[x][p] + solve(x + 1, p, p, 0);
    // Eel decides not to place a wall below the token.
    // In this case, Rabbit must move the token down.
    if (l == 0 && r == m - 1) return res; // Eel can't prevent Rabbit from reaching the bottommost row.
    int val = INF;
    if (r + 1 < m) val = std::min(val, solve(x, l, r + 1, 1) + sum[x][r + 1] - sum[x][p]);
    if (l) val = std::min(val, solve(x, l - 1, r, 0) + sum[x][p + 1] - sum[x][l]);
    // Rabbit will move the token to the position with lower cost.
    res = std::max(res, val);
    // Eel is to maximize the cost.
    return res;
  }
 public:
  int play(vector<string> s) {
    n = s.size(), m = s[0].length();
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        a[i][j] = s[i][j] - '0';
    memset(f, 0x3f, sizeof f);
    memset(sum, 0, sizeof sum);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        sum[i][j + 1] = sum[i][j] + a[i][j];
    int res = INF;
    for (int i = 0; i < m; ++i) res = std::min(res, solve(0, i, i, 0));
    return res;
  }
};

// CUT begin
ifstream data("WallGameDiv1.sample");

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

bool do_test(vector<string> costs, int __expected) {
    time_t startClock = clock();
    WallGameDiv1 *instance = new WallGameDiv1();
    int __result = instance->play(costs);
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
        vector<string> costs;
        from_stream(costs);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(costs, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475800449;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "WallGameDiv1 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
