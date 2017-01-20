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
const int N = 51;
int id[N][N]; 
int f[N * N], cnt[N * N];
int get(int u) { //并查集
    if (u == f[u]) return u;
    return f[u] = get(f[u]);
}
void join(int u, int v) {
    f[get(u)] = get(v);
}

class GooseInZooDivOne {
	public:
		int count(vector<string> field, int dist) {
            int n = field.size(), m = field[0].size();
            int tot = 0;
            REP(i, 0, n - 1) REP(j, 0, m - 1) id[i][j] = ++tot;
            REP(i, 1, tot) f[i] = i, cnt[i] = 0;
            REP(i, 0, n - 1) REP(j, 0, m - 1) if (field[i][j] == 'v') 
                REP(k1, 0, n - 1 ) REP(k2, 0, m - 1) if (k1 != i || k2 != j) 
                if (field[k1][k2] == 'v') if (abs(i - k1) + abs(j - k2) <= dist) join(id[i][j], id[k1][k2]);
            //把两两之间距离小于dist的那些给放到一个集合中去

            REP(i, 0, n - 1) REP(j, 0, m - 1) if (field[i][j] == 'v') cnt[get(id[i][j])]++;
            int ans1 = 0, ans2 = 0;
            REP(i, 0, n - 1) REP(j, 0, m - 1) if (field[i][j] == 'v' && f[id[i][j]] == id[i][j]) {
                if (cnt[id[i][j]] & 1) ++ans1; //集合大小为奇数的集合个数
                else ++ans2; //集合大小为偶数的集合个数
            }
            int ans = pow(2, ans1 + ans2 - (ans1 > 0)); //因为要满足goose的数目为偶数，所以奇数的那些集合只能选偶数个

			return (ans - 1 + mo) % mo;//至少要有一个goose
		}
};

// CUT begin
ifstream data("GooseInZooDivOne.sample");

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

bool do_test(vector<string> field, int dist, int __expected) {
    time_t startClock = clock();
    GooseInZooDivOne *instance = new GooseInZooDivOne();
    int __result = instance->count(field, dist);
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
        vector<string> field;
        from_stream(field);
        int dist;
        from_stream(dist);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, dist, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477053734;
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
        cout << "GooseInZooDivOne (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
