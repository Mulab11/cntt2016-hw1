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
const int N = 310;
int f[2][N][N];// f[i][j][k]代表目前放了前i个位置，i到j位置都不能放wolf了， (j + 1)到k位置可以放一个wolf的方案数
PII a[N]; //所有的区间
int n, m, tmp;
stringstream fin;
class WolfInZooDivOne {
	public:
		int count(int N, vector<string> L, vector<string> R) {
            fin.clear();
            n = N;
            REP(i, 1, L.size() - 1) L[0] += L[i];
            REP(i, 1, R.size() - 1) R[0] += R[i];
            fin << L[0];
            m = 0;
            while (fin >> tmp) a[++m].FR = tmp + 1;
            fin.clear();
            fin << R[0];
            m = 0;
            while (fin >> tmp) a[++m].SC = tmp + 1; //处理一下格式

            sort(a + 1, a + m + 1);
            CL(f, 0);
            f[0][0][0] = 1;
            int j = 1, c = 0, ans = 0, l = 0;
            REP(i, 0, n - 1) {
                c ^= 1; CL(f[c], 0); //滚动数组
                while (j <= m && a[j].FR <= i + 1) getmax(&l, a[j].SC), ++j;//目前包含i + 1这个位置的最远的区间
                REP(k1, 0, n) 
                    REP(k2, k1, n) {
                        f[c][k1][k2] = (f[c][k1][k2] + f[c ^ 1][k1][k2]) % mo; //这个位置不放wolf
                        if (k1 < i + 1) f[c][k2][l] = (f[c][k2][l] + f[c ^ 1][k1][k2]) % mo; //这个位置放wolf
                    }
            }
            REP(i, 0, n) 
                REP(j, i, n) ans = (ans + f[c][i][j]) % mo;

			return ans;
		}
};

// CUT begin
ifstream data("WolfInZooDivOne.sample");

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

bool do_test(int N, vector<string> L, vector<string> R, int __expected) {
    time_t startClock = clock();
    WolfInZooDivOne *instance = new WolfInZooDivOne();
    int __result = instance->count(N, L, R);
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
        int N;
        from_stream(N);
        vector<string> L;
        from_stream(L);
        vector<string> R;
        from_stream(R);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, L, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477270762;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "WolfInZooDivOne (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
