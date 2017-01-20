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
pair<int, LL> b[100];
pair<int, LL> c[100];
int a[100];
int n, m;
bool check(LL x) {
    int j = 1;
    REP(i, 1, m) c[i] = b[i];
    REP(i, 1, n) { //把飞天小女警的能力排序 从小到大做
        LL y = x;
        while (j <= m && a[i] >= c[j].FR && y >= c[j].SC) { // 如果飞天小女警能够干掉这个坏蛋，就干掉
            y -= c[j].SC;
            ++j;
        }
        if (a[i] >= c[j].FR) c[j].SC -= y; //如果飞天小女警比坏蛋强，但是体力不够，就先打掉它一点血
    }
    return j > m;
}
class SpaceWarDiv1 {
	public:
		long long minimalFatigue(vector<int> A, vector<int> B, vector<long long> C) {
            n = A.size(); m = B.size();
            REP(i, 1, n) a[i] = A[i - 1];
            REP(i, 1, m) b[i] = MP(B[i - 1], C[i - 1]);
            LL l = 0, r = 1e18, res = -1;
            sort(b + 1, b + m + 1);
            sort(a + 1, a + n + 1);
            while (l <= r) {//二分答案判断是否合法
                LL mid = (l + r) >> 1;
                if (check(mid)) r = mid - 1, res = mid; 
                else l = mid + 1;
            }
			return res;
		}
};

// CUT begin
ifstream data("SpaceWarDiv1.sample");

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

bool do_test(vector<int> magicalGirlStrength, vector<int> enemyStrength, vector<long long> enemyCount, long long __expected) {
    time_t startClock = clock();
    SpaceWarDiv1 *instance = new SpaceWarDiv1();
    long long __result = instance->minimalFatigue(magicalGirlStrength, enemyStrength, enemyCount);
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
        vector<int> magicalGirlStrength;
        from_stream(magicalGirlStrength);
        vector<int> enemyStrength;
        from_stream(enemyStrength);
        vector<long long> enemyCount;
        from_stream(enemyCount);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(magicalGirlStrength, enemyStrength, enemyCount, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478832773;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SpaceWarDiv1 (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
