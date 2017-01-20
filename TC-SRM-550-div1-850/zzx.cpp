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
int n, m;
int id[N][N];
struct Matrix {
    int a[N][N];
    Matrix() {
        CL(a, 0);
    }
    Matrix(int x) {
        CL(a, 0);
        REP(i, 1, m) a[i][i] = x;
    }
};
Matrix operator *(const Matrix &A, const Matrix &B) {
    Matrix C;
    REP(k, 1, m) 
        REP(i, 1, m) 
            REP(j, 1, m) C.a[i][j] = (C.a[i][j] + 1LL * A.a[i][k] * B.a[k][j] % mo) % mo;
    return C;
}
int b[N];
Matrix pow(Matrix A, int b) {
    Matrix res(1);
    for (int i = 1; i <= b; i <<= 1, A = A * A) if (b & i) res = res * A;
    return res;
}
class ConversionMachine {
	public:
		int countAll(string word1, string word2, vector<int> costs, int maxCost) {
            n = word1.size();
            m = 0;
            Matrix A;
            REP(i, 0, n) REP(j, 0, n - i) id[i][j] = ++m;
            ++m;
            REP(i, 0, n) REP(j, 0, n - i) {
                int x = id[i][j];
                int y;
                if (i) y = id[i - 1][j + 1], A.a[x][y] = i;
                if (j) y = id[i][j - 1], A.a[x][y] = j;
                if (i + j != n) y = id[i + 1][j], A.a[x][y] = n - i - j;
            }
            A.a[m][m] = 1; A.a[id[0][1]][m] = 1;
            int r = 0;
            int x = 0, y = 0;
            bool same = (word1 == word2);
            REP(i, 0, n - 1) {
                int tmp = 0;
                while (word1[i] != word2[i]) {
                    ++tmp;
                    ++r;
                    maxCost -= costs[word1[i] - 'a'];
                    if (maxCost < 0) return 0;
                    word1[i]++;
                    if (word1[i] == 'd') word1[i] = 'a';
                }
                if (tmp == 1) ++y;
                else if (tmp == 2) ++x;
            }
            LL all = costs[0];
            all += costs[1]; all += costs[2];
            if ((LL)maxCost >= all)
            r += (maxCost / all) * 3;
            A = pow(A, r);
			int ans = A.a[id[x][y]][m];
            if (same) ans = (ans + A.a[m][m]) % mo;
            return ans;
		}
};

// CUT begin
ifstream data("ConversionMachine.sample");

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

bool do_test(string word1, string word2, vector<int> costs, int maxCost, int __expected) {
    time_t startClock = clock();
    ConversionMachine *instance = new ConversionMachine();
    int __result = instance->countAll(word1, word2, costs, maxCost);
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
        string word1;
        from_stream(word1);
        string word2;
        from_stream(word2);
        vector<int> costs;
        from_stream(costs);
        int maxCost;
        from_stream(maxCost);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(word1, word2, costs, maxCost, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484717742;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 850 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ConversionMachine (850 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
