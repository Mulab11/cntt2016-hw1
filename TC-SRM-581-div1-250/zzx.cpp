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
const int N = 100;
int s[N], n;
multiset<int> S;
int L;
bool low(int p) {//判断p是否无论如何都不会被监视
    multiset<int> T(S);
    REP(i, 1, n - L + 1) {
        if (i <= p && i + L - 1 >= p) continue;
        int k = s[i + L - 1] - s[i - 1];
        multiset<int>::iterator it = T.find(k);
        if (it != T.end()) T.erase(it);
    }
    return T.empty(); // 如果其他的位置就够了那么p就不一定会被监视了
}
bool high(int p) { //判断p是否一定会被监视 
    multiset<int> T(S);
    REP(i, 1, n - L + 1) {
        if (i <= p && i + L - 1 >= p); else continue;
        int k = s[i + L - 1] - s[i - 1];
        multiset<int>::iterator it = T.find(k);
        if (it != T.end()) T.erase(it);
    }
    return T.size() != S.size(); //只要[p - L + 1, p]这个当中有在集合中的区间就可以了
}
class SurveillanceSystem {
	public:
		string getContainerInfo(string containers, vector<int> reports, int L) {
            ::L = L;
            n = containers.size();
            S.clear();
            for (int i = 0; i < reports.size(); ++i) S.insert(reports[i]);
            s[0] = 0;
            REP(i, 1, n) s[i] = s[i - 1] + (containers[i - 1] == 'X');
            string ans;
            REP(i, 1, n) { //枚举第i个位置 检查其是否一定会被监视或者不被监视
                int l = low(i), r = high(i);
                if (!r) ans += '-'; //i这个位置无论如何都不会被监视
                else if (!l) ans += '+'; //i这个位置一定会被监视
                else ans += '?';//i这个位置可能会被监视
            }
            return ans;
		}
};

// CUT begin
ifstream data("SurveillanceSystem.sample");

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

bool do_test(string containers, vector<int> reports, int L, string __expected) {
    time_t startClock = clock();
    SurveillanceSystem *instance = new SurveillanceSystem();
    string __result = instance->getContainerInfo(containers, reports, L);
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
        string containers;
        from_stream(containers);
        vector<int> reports;
        from_stream(reports);
        int L;
        from_stream(L);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(containers, reports, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1479278035;
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
        cout << "SurveillanceSystem (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
