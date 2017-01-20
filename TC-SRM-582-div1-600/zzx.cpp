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

const int mo = 1000000009;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
const int N = 1300;
int f[N][N]; //i ~ n这些building 能看到j段的方案数 f[i][j] = f[k][j] * C(xx, xx) 如果color[i] = color[k],  f[i][j] = f[k][j - 1]  *C(xx,xx) 如果color[i] != color[k]
int fact[N], inv[N]; //阶乘 和 阶乘的逆元 
int a[N];
int pool[3000000];
int g[N][N];//dp数组的前缀和
int n;
class ColorfulBuilding {
	public:
		int count(vector<string> color1, vector<string> color2, int L) {
            REP(i, 1, color1.size() - 1) color1[0] += color1[i];
            REP(i, 1, color2.size() - 1) color2[0] += color2[i];
            n = color1[0].size();
            REP(i, 1, n) a[i] = 1000 * color1[0][i - 1] + color2[0][i - 1];
            CL(pool, 0);
            REP(i, 1, n) {
                if (!pool[a[i]]) pool[a[i]] = i;
                a[i] = pool[a[i]];
            }
            fact[0] = 1;
            REP(i, 1, n) fact[i] = 1LL * fact[i - 1] * i % mo;
            REP(i, 0, n) inv[i] = pow(fact[i], mo - 2);
            CL(f, 0);
            CL(g, 0);
            f[n][1] = 1;
            g[1][0] = g[1][a[n]] = 1;
            ++L;
            a[0] = n + 1;
            PER(i, n - 1, 0) {
                REP(j, 1, L) {
                    /*
                     * 原本的转移应该是这个样子的
                       REP(k, i + 1, n) 
                       if (a[i] != a[k]) 
                       f[i][j] = (f[i][j] + 1LL * f[k][j - 1] * fact[n - i - 1] % mo * inv[n - k] % mo) % mo;
                       else 
                       f[i][j] = (f[i][j] + 1LL * f[k][j] * fact[n - i - 1] % mo * inv[n - k] % mo) % mo;
                       */
                    int now = (g[j - 1][0] - g[j - 1][a[i]] + mo) % mo; //用前缀和去优化
                    f[i][j] = (f[i][j] + 1LL * fact[n - i - 1] * g[j][a[i]] % mo) % mo;
                    f[i][j] = (f[i][j] + 1LL * fact[n - i - 1] * now % mo) % mo;
                }
                REP(j, 1, L) {
                    g[j][0] = (g[j][0] + 1LL * f[i][j] * inv[n - i] % mo) % mo;
                    g[j][a[i]] = (g[j][a[i]] + 1LL * f[i][j] * inv[n - i] % mo) % mo;
                }
            }
			return f[0][L];
		}
};

// CUT begin
ifstream data("ColorfulBuilding.sample");

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

bool do_test(vector<string> color1, vector<string> color2, int L, int __expected) {
    time_t startClock = clock();
    ColorfulBuilding *instance = new ColorfulBuilding();
    int __result = instance->count(color1, color2, L);
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
        vector<string> color1;
        from_stream(color1);
        vector<string> color2;
        from_stream(color2);
        int L;
        from_stream(L);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(color1, color2, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478916562;
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
        cout << "ColorfulBuilding (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
