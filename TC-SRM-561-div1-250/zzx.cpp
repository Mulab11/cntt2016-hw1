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
vector<int> L, M; //尺寸为L的气球和M的气球
vector<int> A; // A题的人数
int calc(vector<int> A, vector<int> B) { //计算 A与B两个集合要符合条件的最小代价
    int sa = 0, sb = 0;
    for (int i = 0; i < A.size(); ++i) sa += A[i];
    for (int i = 0; i < B.size(); ++i) sb += B[i];
    if (sb > sa) return -1;
    int sum = 0;
    for (int i = 0; i < B.size(); ++i) {
        int x = 0; if (i < A.size()) x = A[i]; //这里使用贪心的想法 把两个集合从小到大配对
        if (x < B[i]) sum += B[i] - x;
    }
    return sum;
}
int check(int S) { //计算当选取大小气球的方案为S的时候的最小代价
    vector<int> X, Y;
    REP(i, 0, A.size() - 1) if (S & (1 << i)) X.PB(A[i]);
    else Y.PB(A[i]);
    sort(X.begin(), X.end(), greater<int>());
    sort(Y.begin(), Y.end(), greater<int>());
    int ans1 = calc(L, X), ans2 = calc(M, Y);
    if (ans1 != -1 && ans2 != -1) return ans1 + ans2;
    return -1;
}
class ICPCBalloons {
	public:
		int minRepaintings(vector<int> balloonCount, string balloonSize, vector<int> maxAccepted) {
            L.clear(); M.clear();
            A = maxAccepted;
            for (int i = 0; i < balloonCount.size(); ++i) if (balloonSize[i] == 'L') 
                L.PB(balloonCount[i]);
            else M.PB(balloonCount[i]);
            sort(L.begin(), L.end(), greater<int>());
            sort(M.begin(), M.end(), greater<int>());

            int ans = -1;

            REP(i, 0, (1 << A.size()) - 1) {//枚举每个题用大气球还是小气球
                int x = check(i); 
                if (x != -1)
                    if (ans == -1 || x < ans) ans = x;
            }
			return ans;
		}
};

// CUT begin
ifstream data("ICPCBalloons.sample");

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

bool do_test(vector<int> balloonCount, string balloonSize, vector<int> maxAccepted, int __expected) {
    time_t startClock = clock();
    ICPCBalloons *instance = new ICPCBalloons();
    int __result = instance->minRepaintings(balloonCount, balloonSize, maxAccepted);
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
        vector<int> balloonCount;
        from_stream(balloonCount);
        string balloonSize;
        from_stream(balloonSize);
        vector<int> maxAccepted;
        from_stream(maxAccepted);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(balloonCount, balloonSize, maxAccepted, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476757648;
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
        cout << "ICPCBalloons (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
