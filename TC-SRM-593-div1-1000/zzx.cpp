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
const int N = 2100000;
char s[N];
int f[N];
int sum1[N], sum2[N]; //奇数下标的前缀和以及偶数下标的前缀和
int sw[N], so[N]; //'w'的前缀和 'o'的前缀和 用于判断子串合法
vector<PII> v; //储存合法的转移区间 不超过O(log(n))
bool check(int i, int j) { //判断[i, j]是否合法 (w^n + o^n)
    if (i <= 0 || i > j || (i - j) % 2 == 0) return false;
    int m = (i + j) / 2;
    return (so[m] - so[i - 1] == 0) && (sw[j] - sw[m] == 0);
}
class WolfDelaymasterHard {
	public:
		int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) {
            //先生成字符串
            //
            REP(i, 1, N) s[i] = '?';
            LL x = w0;
            REP(i, 0, wlen - 1) {
                s[x + 1] = 'w';
                x = (x * wmul + wadd) % N;
            }

            x = o0; 
            REP(i, 0, olen - 1) {
                s[x + 1] = 'o';
                x = (x * omul + oadd) % N;
            }
            sw[0] = so[0] = 0;
            REP(i, 1, N) sw[i] = sw[i - 1] + (s[i] == 'w'), so[i] = so[i - 1] + (s[i] == 'o');
            f[0] = 1;
            f[1] = 0;
            sum2[0] = 1; 
            sum1[1] = 0;
            v.clear();

            REP(i, 2, N) {
                vector<PII> t;
                bool flag = false;
                for (int j = 0; j < v.size(); ++j) { //维护合法的转移区间
                    PII &A = v[j];
                    if (!check(i - 2 * A.SC - 1, i)) --A.SC;
                    A.SC++, A.FR++;
                    if (A.FR <= A.SC) {
                        if (A.FR == 2 && check(i - 1, i)) A.FR = 1, flag = 1;
                        if (s[i] != 'w')
                            t.PB(A);
                    }
                }
                if (!flag && check(i - 1, i)) t.PB(MP(1, 1));
                v = t;
                int *s;
                if (i & 1) s = sum1;
                else s = sum2;

                f[i] = 0;
                for (int j = 0; j < v.size(); ++j) {
                    PII &A = v[j];
                    f[i] = (f[i] + s[i - 2 * A.FR] - s[i - 2 * A.SC]) % mo; //通过前缀和来计算
                    f[i] = (f[i] + f[i - 2 * A.SC]) % mo;
                    if (f[i] < 0) f[i] += mo;
                }
                s[i] = (s[i - 2] + f[i]) % mo;
            }
			return f[N];
		}
};

// CUT begin
ifstream data("WolfDelaymasterHard.sample");

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

bool do_test(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd, int __expected) {
    time_t startClock = clock();
    WolfDelaymasterHard *instance = new WolfDelaymasterHard();
    int __result = instance->countWords(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd);
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
        int N;
        from_stream(N);
        int wlen;
        from_stream(wlen);
        int w0;
        from_stream(w0);
        int wmul;
        from_stream(wmul);
        int wadd;
        from_stream(wadd);
        int olen;
        from_stream(olen);
        int o0;
        from_stream(o0);
        int omul;
        from_stream(omul);
        int oadd;
        from_stream(oadd);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, wlen, w0, wmul, wadd, olen, o0, omul, oadd, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476866200;
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
        cout << "WolfDelaymasterHard (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
