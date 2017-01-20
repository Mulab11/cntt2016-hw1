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
string b[N];
string T;
int n, m;
int tmp[N], sum[N], len[N];
int f[N];
int trans(int x) {
    int res = 0;
    REP(i, 0, b[x].size() - 1) res += (b[x][i] != T[i]);
    return res;
}
int solve1() {
    T = b[0];
    int ans = 1e9;
    REP(i, 0, (1 << m) - 1) {
        REP(j, 0, m - 1) if (i & (1 << j)) T[j] = '1'; else T[j] = '0';
        REP(j, 0, n - 1) tmp[j] = trans(j);
        sum[0] = tmp[0]; len[0] = b[0].size();
        REP(j, 1, n - 1) sum[j] = sum[j - 1] + tmp[j], len[j] = len[j - 1] + b[j].size();
        REP(j, 0, n - 1) {
            f[j] = min(sum[j], len[j] - sum[j] + 1);
            if (j) getmin(&f[j], f[j - 1] + tmp[j]);
            REP(k, 1, j) getmin(&f[j], f[k - 1] + len[j] - len[k - 1] - sum[j] + sum[k - 1] + 2);
        }
        getmin(&ans, f[n - 1]);
    }
    return ans;
}
int calc(int s) {
    int ans = 0;
    int last = -2;
    REP(i, 0, n - 1) if (s & (1 << i)) {
        if (i != last + 1) ++ans;
        last = i;
    }
    ans *= 2;
    if (s & 1) ans --;
    return ans;
}
int solve2() {
    int ans = 1e9;
    int num[2][N];
    REP(i, 0, (1 << n) - 1) {
        int tmp = 0;
        CL(num, 0); 
        REP(j, 0, n - 1) 
            REP(k, 0, b[j].size() - 1) if (i & (1 << j)) num[b[j][k] == '0'][k]++;
        else num[b[j][k] == '1'][k]++;
        REP(j, 0, m - 1) tmp += min(num[0][j], num[1][j]);
        getmin(&ans, tmp + calc(i));
    }
    return ans;
}
class FlippingBitsDiv1 {
	public:
		int getmin(vector<string> S, int M) {
            for (int i = 1; i < S.size(); ++i) S[0] += S[i];
            m = M;
            REP(i, 0, 300) b[i].clear();
            REP(i, 0, S[0].size() - 1) {
                b[i / M] += S[0][i];
            }
            n = (S[0].size() - 1) / M + 1;
            int ans = 0;
            if (M <= 17) ans = solve1();
            else ans = solve2();
			return ans;
		}
};

// CUT begin
ifstream data("FlippingBitsDiv1.sample");

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

bool do_test(vector<string> S, int M, int __expected) {
    time_t startClock = clock();
    FlippingBitsDiv1 *instance = new FlippingBitsDiv1();
    int __result = instance->getmin(S, M);
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
        vector<string> S;
        from_stream(S);
        int M;
        from_stream(M);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476961526;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FlippingBitsDiv1 (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
