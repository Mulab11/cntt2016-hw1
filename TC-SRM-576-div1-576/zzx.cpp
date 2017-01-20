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

const int mo = 1000000009;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
const int N = 610;
int f[N][N][3]; //first i drops, j intervals, 0 : i isn't picked, 1 : i is picked but this consecutive intervals doesn't have any L width interval, 2: very good
int s[N];
int a[N], n, m;
int A, B, L;
class TheExperiment {
	public:
		int countPlacements(vector<string> intensity, int M, int L, int A, int B) {
            n = 0, m = M;
            REP(i, 0, intensity.size() - 1) REP(j, 0, intensity[i].size() - 1) a[++n] = intensity[i][j] - '0';
            ::A = A, ::B = B;
            ::L = L;
            REP(i, 1, n) s[i] = s[i - 1] + a[i];
            CL(f, 0);
            f[0][0][0] = 1;
            REP(i, 1, n) {
                REP(j, 0, m) {
                    f[i][j][0] = (f[i - 1][j][0] + f[i - 1][j][2]) % mo; // 要么是前面也是空的，要么是前面是组好的一段
                    if (j)  {
                        PER(k, i - 1, max(0, i - L +  1)) if (s[i] - s[k] <= B && s[i] - s[k] >= A) // 枚举这一段的长度
                            f[i][j][1] = ((f[i][j][1] + f[k][j - 1][1]) % mo + f[k][j - 1][0]) % mo;//有可能是新的一个连续段

                        PER(k, i - 1, max(0, i - L + 1)) if (s[i] - s[k] <= B && s[i] - s[k] >= A) // 枚举这一段的长度
                            f[i][j][2] = (f[i][j][2] + f[k][j - 1][2]) % mo;//有可能是新的一个连续段

                        if (i >= L && s[i] - s[i - L] >= A &&  s[i] - s[i - L] <= B) { // 这一段长度为L
                            f[i][j][2] = (f[i][j][2] + f[i - L][j - 1][2]) % mo;
                            f[i][j][2] = (f[i][j][2] + f[i - L][j - 1][1]) % mo;
                            f[i][j][2] = (f[i][j][2] + f[i - L][j - 1][0]) % mo;
                        }

                    }
                }
            }
            int ans = 0;
            REP(i, 1, n) ans = (ans + f[i][m][2]) % mo;
			return ans;
		}
};

// CUT begin
ifstream data("TheExperiment.sample");

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

bool do_test(vector<string> intensity, int M, int L, int A, int B, int __expected) {
    time_t startClock = clock();
    TheExperiment *instance = new TheExperiment();
    int __result = instance->countPlacements(intensity, M, L, A, B);
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
        vector<string> intensity;
        from_stream(intensity);
        int M;
        from_stream(M);
        int L;
        from_stream(L);
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(intensity, M, L, A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477623214;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 576 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheExperiment (576 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
