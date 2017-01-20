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
const int N = 300;
int n, m;
PII w[N], b[N];
stringstream fin;
LL area(PII A, PII B, PII C){
    A.FR -= C.FR, A.SC -= C.SC;
    B.FR -= C.FR, B.SC -= C.SC;
    return 1LL * A.FR * B.SC - 1LL * A.SC * B.FR;
}
bool check(PII &X, PII &Y) {
    int l = 0, r = 0;
    REP(i, 1, n) {
        if (area(w[i], Y, X) < 0) ++l;
        else if (area(w[i], Y, X) > 0) ++r;
    }
    if (l && r) return false;

    int l2 = 0, r2 = 0;

    REP(i, 1, m) {
        if (area(b[i], Y, X) < 0) ++l2;
        else if (area(b[i], Y, X) > 0) ++r2;
    }
    if(l2 && r2) return false;
    if (l && l2) return false;
    if (r && r2) return false;
    return true;
}

bool checkW(PII &X, PII &Y) {
    int l = 0, r = 0;
    REP(i, 1, n) {
        if (area(w[i], Y, X) < 0) ++l;
        else if (area(w[i], Y, X) > 0) ++r;
    }
    if (l && r) return false;
    return true;
}

bool checkB(PII &X, PII &Y) {
    int l = 0, r = 0;
    REP(i, 1, n) {
        if (area(b[i], Y, X) < 0) ++l;
        else if (area(b[i], Y, X) > 0) ++r;
    }
    if (l && r) return false;
    return true;
}
class CheckerFreeness {
	public:
		string isFree(vector<string> wX, vector<string> wY, vector<string> bX, vector<string> bY) {
            n = m = 0;
            fin.clear();
            REP(i, 0, wX.size() - 1) fin << wX[i];
            while (fin >> w[++n].FR);

            n = 0;
            fin.clear();
            REP(i, 0, wY.size() - 1) fin << wY[i];
            while (fin >> w[++n].SC);
            --n;

            m = 0;
            fin.clear();
            REP(i, 0, bX.size() - 1) fin << bX[i];
            while (fin >> b[++m].FR);

            m = 0;
            fin.clear();
            REP(i, 0, bY.size() - 1) fin << bY[i];
            while (fin >> b[++m].SC);
            --m;
            if (n == 1 || m == 1) return "YES";
            REP(i, 1, n) {
                REP(j, 1, m) if (check(w[i], b[j])) return "YES"; //先判断W和B的区域是否不交
            }
            bool flag = 1;
            REP(i, 1, n) 
                REP(j, i + 1, n) if (!checkB(w[i], w[j])) flag = 0; //判断W是否完全包含B
            if (flag) return "YES";
            flag = 1;
            REP(i, 1, m) 
                REP(j, i + 1, m) if (!checkW(b[i], b[j])) flag = 0;//判断B是否完全包含W
            if (flag) return "YES";
			return "NO";
		}
};

// CUT begin
ifstream data("CheckerFreeness.sample");

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

bool do_test(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY, string __expected) {
    time_t startClock = clock();
    CheckerFreeness *instance = new CheckerFreeness();
    string __result = instance->isFree(whiteX, whiteY, blackX, blackY);
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
        vector<string> whiteX;
        from_stream(whiteX);
        vector<string> whiteY;
        from_stream(whiteY);
        vector<string> blackX;
        from_stream(blackX);
        vector<string> blackY;
        from_stream(blackY);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(whiteX, whiteY, blackX, blackY, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1478591524;
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
        cout << "CheckerFreeness (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
