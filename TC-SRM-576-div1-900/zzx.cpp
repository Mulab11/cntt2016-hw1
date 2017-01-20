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
int w;
LL id(int x, int y) {
    return 1LL * w * x + y; //计算一个元素的位置
}
map<LL, char> S;
set<LL> A;
vector<LL> v[255];  //把所有相同的字符放在一起
int n, m;
void frac(LL x) { //寻找x的所有因子
    if (A.find(x) != A.end()) return; //总共不同的差的数量不会超过100
    for (LL i = 1; i * i <= x; ++i) if (x % i == 0) {
        A.insert(i);
        if (i * i != x) A.insert(x / i);
    }
}
int check(LL x) {//计算S长度为x的时候的合法的S的数量
    static map<LL, char> C; C.clear();
    for (map<LL, char> ::iterator it = S.begin(); it != S.end(); ++it) {
        if (C.find(it -> FR % x) == C.end()) C[it -> FR % x] = it -> SC;
        else if (C[it -> FR % x] != it -> SC) return 0;
    }
    return pow(26, (int)x - (int)C.size());
}

class CharacterBoard {
	public:
		int countGenerators(vector<string> fragment, int W, int i0, int j0) {
            S.clear();
            A.clear();
            w = W;
            n = fragment.size(), m = fragment[0].size();
            REP(i, 0, n - 1) REP(j, 0, m - 1) 
                S[id(i + i0, j + j0)] = fragment[i][j]; 
            int ans = 0;
            if (W >= n * m) 
                ans = 1LL * (pow(26, W - n * m + 1) - 1 + mo) % mo * pow(25, mo - 2) % mo; //先计算不会产生重叠部分的答案

            for (map<LL, char> ::iterator it = S.begin(); it != S.end(); ++it) 
                for (map<LL, char> ::iterator it2 = it; it2 != S.end(); ++it2) {//枚举所有两两重叠的时候可能的S的长度
                    if ((*it) == (*it2)) continue;
                    frac(it2 -> FR - it -> FR);
                }
            for (set<LL> ::iterator it = A.begin(); it != A.end(); ++it) {
                if (*it > W) break;
                int tmp = check(*it);
                ans = (ans + tmp) % mo;
                if ((*it) >= n * m) ans = (ans - pow(26LL, (*it) - n * m) + mo) %mo; //如果长度大于n * m那么就要把之前的计算给减去
            }


			return ans;
		}
};

// CUT begin
ifstream data("CharacterBoard.sample");

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

bool do_test(vector<string> fragment, int W, int i0, int j0, int __expected) {
    time_t startClock = clock();
    CharacterBoard *instance = new CharacterBoard();
    int __result = instance->countGenerators(fragment, W, i0, j0);
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
        vector<string> fragment;
        from_stream(fragment);
        int W;
        from_stream(W);
        int i0;
        from_stream(i0);
        int j0;
        from_stream(j0);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(fragment, W, i0, j0, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477897486;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CharacterBoard (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
