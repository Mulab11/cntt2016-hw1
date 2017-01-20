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
typedef unsigned long long ULL;
const int N = 100;
map<ULL, string> S;
string s[N];
int num[N];
int n, m;
ULL magic;
int getsame1(string A, string B) { // check the same number of digits of A and B
	int ans = 0;
	REP(i, 0, m / 2 - 1) ans += (A[i] == B[i]);
	return ans;
}
int getsame2(string A, string B) {
	int ans = 0;
	REP(i, m / 2, m - 1) ans += (A[i - m / 2] == B[i]);
	return ans;
}
ULL h1(string x) { // hashing
	ULL r = 0;
	REP(i, 1, n) {
		int t = num[i] - getsame1(x, s[i]);
		if (t < 0) return magic;
		r = r * 1331 + t;
	}
	return r;
}
ULL h2(string x) { // hashing
	ULL r = 0;
	REP(i, 1, n) {
		int t = getsame2(x, s[i]);
		if (t < 0) return magic;
		r = r * 1331 + t;
	}
	return r;
}
void dfs1(int dep, string now) { // enumerater first m / 2 digits
	if (dep == m / 2) {
		ULL t = h1(now);
		if (t != magic) {
			if (S.find(t) == S.end()) S[t] = now;
			else S[t] = "A";
		}
		return;
	}
	REP(i, '0', '9') dfs1(dep + 1, now + (char)i);
}
string ans;
void dfs2(int dep, string now) { // enumerate the latter m / 2 digits
	if (dep == m) {
		ULL t = h2(now);
		if (t != magic){
			if (S.find(t) != S.end()) {
				if (ans == "") ans = S[t] + now;
				else ans = "A";
			}
		}
		return;
	}
	REP(i, '0', '9') dfs2(dep + 1, now + (char)i);
}

class EllysBulls {
	public:
		string getNumber(vector<string> g, vector<int> bulls) {
			magic = 19981103;
			REP(i, 1, 10) magic *= (rand() + 1); // magic number means invalid situations
			S.clear();
			m  = g[0].size();
			n = g.size();
			REP(i, 1, n) s[i] = g[i - 1], num[i] = bulls[i - 1];
			ans = "";
			dfs1(0, ""); // meet in the middle strategy
			dfs2(m / 2, "");
			if (ans[0] == 'A') return "Ambiguity"; // if we found multiple answers 
			if (ans == "") return "Liar";// no answer
			return ans;
		}
};

// CUT begin
ifstream data("EllysBulls.sample");

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

bool do_test(vector<string> guesses, vector<int> bulls, string __expected) {
    time_t startClock = clock();
    EllysBulls *instance = new EllysBulls();
    string __result = instance->getNumber(guesses, bulls);
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
        vector<string> guesses;
        from_stream(guesses);
        vector<int> bulls;
        from_stream(bulls);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(guesses, bulls, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1481873510;
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
        cout << "EllysBulls (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
