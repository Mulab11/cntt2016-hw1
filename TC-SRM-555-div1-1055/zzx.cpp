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
/*
 * inclusive-exlusive principle
 * we can count the number of different string when we start at each digit
 * however, there are several strings which can be counted multiple times 
 * we need inclusive-exlusive principle
 * first we can calulate the fixed digits if we started at i-th digit, we denote it Si
 * if a string T will be counted in i, j then it must have digit in Si & Sj
 */
const int N = 100;
LL s[N], all, t;
string c;
int n, m;
LL calc(int p) { // calculate the maximum fixed digits when we start at p
    LL r = 0, tmp = 0, ans = 0;
    REP(i, 0, m - 1) {
        if (c[i] == '>') ++p;
        else if (c[i] == '<') --p;
        else if (c[i] == '1') tmp |= (1LL << p), r |= (1LL << p);
        else tmp |= (1LL << p), r &= (all - (1LL << p));
        if (r == (tmp & t)) ans = tmp;
    }
    return ans;
}
int ll, rr, cur;
LL solve(int k, LL sta, int num) { // DFS inclusive-exlusive
    if (k > rr) {
        if (num & 1) return (1LL << __builtin_popcountll(sta));
        else if (num) return -(1LL << __builtin_popcountll(sta));
        else return 0;
    }
    if (!sta) return 0; // important optimization reduce the number of status from 2 ^ n to 2 ^ (n / 2)
    return solve(k + 1, sta, num) + solve(k + 1, sta & s[k], num + 1);
}
class MapGuessing {
	public:
		long long countPatterns(string goal, vector<string> code) {
            n = goal.size();
            t = 0; c = "";
            REP(i, 0, n - 1) if (goal[i] == '1') t |= (1LL << i);
            all = (1LL << n) - 1;
            for (int i = 0; i < code.size(); ++i) c += code[i];
            m = c.size();
            ll = 0, rr = 0, cur = 0;
            REP(i, 0, m - 1) {
                if (c[i] == '>') ++cur;
                else if (c[i] == '<') --cur;
                getmin(&ll, cur); getmax(&rr, cur);
            }
            ll = -ll; rr = n - 1 - rr;
            if (ll > rr) return 0; // left valid bound and right valid bound
            REP(i, ll, rr) s[i] = calc(i);
            return solve(ll, all, 0);
		}
};

// CUT begin
ifstream data("MapGuessing.sample");

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

bool do_test(string goal, vector<string> code, long long __expected) {
    time_t startClock = clock();
    MapGuessing *instance = new MapGuessing();
    long long __result = instance->countPatterns(goal, code);
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
        string goal;
        from_stream(goal);
        vector<string> code;
        from_stream(code);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(goal, code, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484201982;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1055 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MapGuessing (1055 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
