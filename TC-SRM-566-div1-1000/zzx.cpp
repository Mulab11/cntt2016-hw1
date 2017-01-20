/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <bitset>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
	if (b < *a) {
		*a = b;
		return true;
	}
	return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
	if (b > *a) {
		*a = b;
		return true;
	}
	return false;
}

const int mo = 100007;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
#include <bitset>
const int N = 300;
const double pi = acos(-1);
bitset<50> S[N][N];
bitset<256> C[N][N];
double x[N], y[N], px[N], py[N];
bool vis[N][N];
char c[N];
int n, m;
int f[N][N], g[N][N], h[N][N][2];
double area(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}
void init(int a, int b) {
    REP(i, 0, m - 1) 
        if (area(px[i] - x[a], py[i] - y[a], x[b] - x[a], y[b] - y[a]) < 0) S[a][b].set(i), C[a][b].set(c[i]);
}
class FencingPenguins {
	public:
		int countWays(int numPosts, int radius, vector<int> X, vector<int> Y, string color) {
            n = numPosts, m = X.size();
            REP(i, 0, n - 1) {
                double d = 2.0 * pi * i / n;
                x[i] = cos(d) * radius;
                y[i] = sin(d) * radius;
            }
            REP(i, 0, m - 1) px[i] = X[i], py[i] = Y[i], c[i] = color[i];
            REP(i, 0, n - 1) 
                REP(j, 0, n - 1) S[i][j].reset(), C[i][j].reset(), init(i, j);
            if (S[0][n - 1].any()) return 0;
            REP(i, 0, n - 1) REP(j, 0, n - 1) vis[i][j] = (C[i][j] & C[j][i]).none();
            CL(h, 0); CL(f, 0); CL(g, 0);
            REP(i, 0, n - 1) h[i][i][1] = 1;
            REP(l, 1, n - 1) {
                REP(i, 0, n - l - 1) {
                    int j = i + l;
                    REP(p, 0, 1) {
                        REP(k, i + 1, j) if (vis[i][k]) {
                            bitset<50> tmp = S[i][k] & S[j][i] & S[k][j];
                            int pp = p | (tmp.any());
                            int res = h[k][j][pp];
                            if (S[k][i].none()) h[i][j][p] = (h[i][j][p] + res) % mo;
                            else if (k - i >= 4 && (S[k][i] & S[i + 1][k - 1]).none())
                                h[i][j][p] = (h[i][j][p] + 1LL * res * f[i + 1][k - 1] % mo) % mo;
                        }
                    }

                    PER(k, j, i + 2) if (vis[i][k]) {
                        int res = h[i][k][0];
                        bitset<50> tmp = S[j][i] & S[i][k];
                        if (tmp.none()) g[i][j] = (g[i][j] + res) % mo;
                        else if (k + 2 < j) {
                            if ((tmp & S[k + 1][j]).none()) g[i][j] = (g[i][j] + 1LL * res * f[k + 1][j] % mo) % mo;
                        }
                    }
                    REP(k, i, j - 1) {
                        bitset<50> tmp = S[j][i] & S[k][j];
                        if (tmp.none()) f[i][j] = (f[i][j] + g[k][j]) % mo;
                    }
                }
            }
			return f[0][n - 1];
		}
};

// CUT begin
ifstream data("FencingPenguins.sample");

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

bool do_test(int numPosts, int radius, vector<int> x, vector<int> y, string color, int __expected) {
    time_t startClock = clock();
    FencingPenguins *instance = new FencingPenguins();
    int __result = instance->countWays(numPosts, radius, x, y, color);
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
        int numPosts;
        from_stream(numPosts);
        int radius;
        from_stream(radius);
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        string color;
        from_stream(color);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numPosts, radius, x, y, color, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484288170;
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
        cout << "FencingPenguins (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
