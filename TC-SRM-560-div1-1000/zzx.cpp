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

const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
const int N = 20;
bool G[N][N]; //邻接矩阵
int M, a[N], n;//a[i]代表未被分配到极值的点i 与其相邻的极值点的点权和 M为非极值点的点权和
double f[N];
/*
 * f[i]为每个点所分配的值
 * 现在要最大化：sigma f[i] * (a[i] + M / 2 - f[i] / 2)
 * 其中sigma f[i] * M / 2的值已经固定 
 * f[i] * a[i] - f[i] ^ 2 / 2 的导数是 a[i] - f[i]
 * 根据拉格朗日乘数法可知一定存在一个数C, 满足
 * a[i] - f[i] + c = 0
 * 由于f[i]的和是M，这样就可以计算得到C的值了
 */

bool isClique(int S) {//判断一个集合是否构成了一个clique
    REP(i, 0, n - 1) if (S & (1 << i)) 
        REP(j, i + 1, n - 1) if (S & (1 << j)) 
            if (!G[i][j]) return false;
    return true;
}
class BoundedOptimization {
	public:
		double maxValue(vector<string> expr, vector<int> lowerBound, vector<int> upperBound, int maxSum) {
            n = lowerBound.size();
            REP(i, 1, expr.size() - 1) expr[0] += expr[i];
            CL(G, 0);
            for (int i = 0; i < expr[0].size(); i += 3) 
                G[expr[0][i] - 'a'][expr[0][i + 1] - 'a'] = 
                    G[expr[0][i + 1] - 'a'][expr[0][i] - 'a'] = 1; //把相邻的点连边

            double ans = 0;

            REP(S, 0, (1 << n) - 1) { //枚举取到极值的点的集合
                if (!isClique((1 << n) - 1 - S)) continue; //所有没取到极值的点要在一个团里面
                for (int T = S; ; T = (T - 1) & S) { //枚举取到lowerbound的点
                    M = maxSum;
                    double tmp = 0;
                    int k = __builtin_popcount((1 << n) - 1 - S); //计算未被分配到值的点的个数
                    int sa = 0;
                    REP(i, 0, n - 1) if (S & (1 << i)) {
                        if (T & (1 << i)) f[i] = lowerBound[i];
                        else f[i] = upperBound[i];
                        M -= f[i];
                    }
                    if (M < 0) goto LOOP; //第一步分配不能超过上限
                    REP(i, 0, n - 1) {
                        if (S & (1 << i)) continue;
                        a[i] = 0;
                        REP(j, 0, n - 1) if (S & (1 << j)) if (G[i][j]) a[i] += f[j]; //a[i]代表与点i相邻的已经分配的点的权值和
                        sa += a[i]; //a[i]的和
                    }
                    REP(i, 0, n - 1) {
                        if (S & (1 << i)) continue;
                        f[i] = 1.0 * a[i] + 1.0 * M / k - 1.0 * sa / k; //根据导数计算每点应该分配的值
                        if (f[i] < 1.0 * lowerBound[i] || f[i] > 1.0 * upperBound[i]) goto LOOP;
                    }
                    REP(i, 0, n - 1) 
                        REP(j, i + 1, n - 1) if (G[i][j]) tmp += f[i] * f[j];
                    getmax(&ans, tmp);
LOOP:               if (!T) break;
                }
            }
			return ans;
		}
};

// CUT begin
ifstream data("BoundedOptimization.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> expr, vector<int> lowerBound, vector<int> upperBound, int maxSum, double __expected) {
    time_t startClock = clock();
    BoundedOptimization *instance = new BoundedOptimization();
    double __result = instance->maxValue(expr, lowerBound, upperBound, maxSum);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<string> expr;
        from_stream(expr);
        vector<int> lowerBound;
        from_stream(lowerBound);
        vector<int> upperBound;
        from_stream(upperBound);
        int maxSum;
        from_stream(maxSum);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(expr, lowerBound, upperBound, maxSum, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477355184;
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
        cout << "BoundedOptimization (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
