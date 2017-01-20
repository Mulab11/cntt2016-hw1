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
#include <cmath>
#include <string>
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

/*======================= TEMPLATE =======================*/
const int N = 500000;
LL gcd(LL a, LL b) {
    if (!b) return a;
    return gcd(b, a % b);
}
LL Sqrt(LL a) { //计算[a^0.5]
    LL t = sqrt(1.0 * a);
    while (t * t > a) --t;
    while ((t + 1) * (t + 1) <= a) ++t;
    return t;
}
LL Sqrt3(LL a) { //计算[a ^1/3]
    LL t = pow(1.0 * a, 0.33333333333333333);
    while (t * t * t > a) --t;
    while ((t + 1) * (t + 1) * (t + 1) <= a) ++t;
    return t;
}
LL S[N], C[N], mu[N]; //S[i]代表i是否有平方因子 C代表立方因子 
vector<int> G[20001]; // G[i][j] = sigma S[i], S[i * 2] .. S[i * j]
vector<int> fac[20001]; //fac存储一个数所有的因子
void calc(int x) { //预处理
    int y = x;
    S[y] = C[y] = mu[y] = 1;
    for (int i = 2; i * i <= y; ++i) if (x % i == 0){
        int num = 0;
        while (x % i == 0) x /= i, ++num;
        if (num > 1) mu[y] = 0; else mu[y] = -mu[y];
        if (num >= 2) S[y] = 0;
        if (num >= 3) C[y] = 0;
        if (x == 1) break;
    }
    if (x > 1) mu[y] = -mu[y];
    if (y <= 20000) {
        fac[y].clear();
        for (int i = 1; i * i <= y; ++i) if (y % i == 0) {
            fac[y].PB(i);
            if (i * i != y) 
                fac[y].PB(y /i);
        }
    }
}
LL solve(LL n) { //计算1-n有多少数合法
    LL ans = 0;
    for (LL i = 1; i * i * i <= n; ++i) if (S[i]) ans += Sqrt(n / i) - i; //首先计算c=2的情况,  如果有多个拆分，取b最小的
    for (LL b = 1; b * b * b * b <= n; ++b) if (C[b]) { //计算c = 3且不能被拆成c = 2的情况
        for (LL k = 1; k * k * k <= b; ++k) {
            LL k1 = k * k / gcd(b, k * k);
            LL b1 = b / gcd(b, k * k);
            if (!S[b1]) continue;
            for (int j = 0; j < fac[b1].size(); ++j) {
                int d = fac[b1][j];
                ans += mu[d] * (G[d][Sqrt3(n / b) / k1 / d] - G[d][b / k1 / d]);
            }
        }
    }
    return ans;
}
class SemiPerfectPower {
	public:
		long long count(long long L, long long R) {
            int T = Sqrt3(R);
            REP(i, 1, T) calc(i);
            REP(i, 1, 20000) {
                G[i].clear();
                G[i].PB(0);
                for (LL j = 1; j * i <= T; ++j) G[i].PB(G[i][j - 1] + S[j * i]);
            }
            return solve(R) - solve(L - 1);
		}
};

// CUT begin
ifstream data("SemiPerfectPower.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(long long L, long long R, long long __expected) {
    time_t startClock = clock();
    SemiPerfectPower *instance = new SemiPerfectPower();
    long long __result = instance->count(L, R);
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
        long long L;
        from_stream(L);
        long long R;
        from_stream(R);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(L, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478930662;
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
        cout << "SemiPerfectPower (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
