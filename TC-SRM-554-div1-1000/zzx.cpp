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

const LL mo = 1234567891;

/*======================= TEMPLATE =======================*/
int n;
int c, k;
struct Matrix {
    LL a[130][130];
    Matrix() {
        CL(a, 0);
    }
    Matrix(int x) {
        CL(a, 0);
        REP(i, 1, n) a[i][i] = x;
    }
    void clear() {
        CL(a, 0);
    }
}A;
Matrix operator * (const Matrix &A, const Matrix &B) {
    Matrix C;
    REP(i, 1, n)
        REP(j, 1, n) {
            REP(k, 1, n) {
                C.a[i][j] += A.a[i][k] * B.a[k][j] % mo;
                if (C.a[i][j] >= 8e18) C.a[i][j] %= mo;
            }
            C.a[i][j] %= mo;
        }
    return C;
        
}

Matrix pow(Matrix &A, LL b) {
    Matrix res(1);
    for (LL i = 1; i <= b; i <<= 1, A = A * A) if (b & i) res = res * A;
    return res;
}

typedef pair<vector<int>, int>  PN;

map<PN, int> S;
LL cnt[130];

int check(vector<int> sta) {
    int ans = (int)(sta[0] == sta[1]) + (int)(sta[0] == sta[2]) + (int)(sta[1] == sta[3]) + (int)(sta[2] == sta[3]);
    return ans;
}

int pd(vector<int> A, vector<int> B) {
    int ans = 0;
    REP(i, 0, 3) ans += (A[i] == B[i]);
    return ans;
}

void dfs(int dep, vector<int> sta, int use, LL tmp) {
    if (dep == 4) {
        int num = check(sta);
        if (num > k) return;
        cnt[n + 1] = tmp;
        REP(i, num, k) S[MP(sta, i)] = ++n;
        return;
    }
    REP(i, 1, use) {
        vector<int> xx = sta;
        xx.PB(i);
        dfs(dep + 1, xx, use, tmp);
    }
    if (use < c) {
        sta.PB(use + 1);
        dfs(dep + 1, sta, use + 1, tmp * (c - use) % mo);
    }
}

void encode(vector<int> &A) {
    int vis[10]; CL(vis, 0);
    int num = 0;
    REP(i, 0, A.size() - 1) {
        if (!vis[A[i]]) vis[A[i]] = ++num;
        A[i] = vis[A[i]];
    }
}

int use(vector<int> A) {
    int res = 0;
    REP(i, 0, A.size() - 1) {
        getmax(&res, A[i]);
    }
    return res;
}
void add(PN A, vector<int> B, int use, LL tmp) {
    if (B.size() == 4) {
        int ans = pd(A.FR, B);
        int kk = A.SC + ans + check(B);
        if (kk > k) return;
        encode(B);
        (::A.a[S[A]][S[MP(B, kk)]] += tmp) %= mo;
        (::A.a[S[A]][n] += tmp) %= mo;
        return;
    }
    REP(i, 1, use) {
        vector<int> xx = B;
        xx.PB(i);
        add(A, xx, use, tmp);
    }
    if (use < c) {
        B.PB(use + 1);
        add(A, B, use + 1, tmp * (c - use));
    }
}


class TheBrickTowerHardDivOne {
	public:
		int find(int C, int K, long long H) {
            c = C; k = K;
            n = 0;
            S.clear();
            A.clear();
            vector<int> v;
            dfs(0, v, 0, 1); // dfs把所有合法的状态都找出来
            REP(i, 1, n) {
                cnt[n + 1] += cnt[i];
                assert(cnt[i] >= 0);
                cnt[n + 1] %= mo;
            }
            ++n;
            for (map<PN, int> ::iterator it = S.begin(); it != S.end(); ++it) {
                vector<int> v;
                add(it -> FR, v, use(it -> FR.FR), 1); //dfs把所有合法的转移都找出来
            }
            A.a[n][n] = 1;
            A = pow(A, H - 1);
            LL ans = 0;
            REP(i, 1, n) ans = (ans + cnt[i] * A.a[i][n] % mo) % mo;
			return ans;
		}
};

// CUT begin
ifstream data("TheBrickTowerHardDivOne.sample");

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

bool do_test(int C, int K, long long H, int __expected) {
    time_t startClock = clock();
    TheBrickTowerHardDivOne *instance = new TheBrickTowerHardDivOne();
    int __result = instance->find(C, K, H);
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
        int C;
        from_stream(C);
        int K;
        from_stream(K);
        long long H;
        from_stream(H);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(C, K, H, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477920552;
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
        cout << "TheBrickTowerHardDivOne (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
