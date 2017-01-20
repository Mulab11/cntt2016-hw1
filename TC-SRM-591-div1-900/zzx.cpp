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
const int N = 10;
struct node { //dp状态
    int x, y; //目前已经dp到了(x, y)
    string s; //目前上面一列的状态 0 代表都不行 1代表可以作为A的结尾 2代表可以作为B的结尾
    node() {}
    node (int _x, int _y, string _s): x(_x) , y(_y), s(_s) {}
};
bool operator < (const node &A, const node &B) {
    if (MP(A.x, A.y) == MP(B.x, B.y)) return A.s < B.s;
    return MP(A.x, A.y) < MP(B.x, B.y);
}
map<node, int> S; //用map来记录所有状态
void add(char &x,  int a) {  //把这个位置打上标记 说明可以放a
    if (x == '3') return;
    if (x - '0' == a) return;
    x += a;
}
bool check(string &x, int k, int a) { //检查位置k是否能作为a的结尾
    if (k < 0) return false;
    if (x[k] == '3') return true;
    return x[k] - '0' == a;
}
queue<node> q;
class StringPath {
	public:
		int countBoards(int n, int m, string A, string B) {
            if (A[0] != B[0]) return 0;
            int ans = 0;
            while (!q.empty()) q.pop();
            S.clear();
            string s,zero;
            REP(i, 0, m - 1) s.PB('0'), zero.PB('0');
            s[0] = '3';
            q.push(node(0, 0, s));
            S[node(0, 0, s)] = 1; //初始状态 

            while (!q.empty()) {
                node now = q.front(); q.pop();
                int i = now.x, j = now.y;
                ++j; if (j >= m) ++i, j = 0;
                int tmp = S[now];
                if (i >= n) { //已经dp完了
                    if (now.s[m - 1] == '3') 
                        ans = (ans + tmp) % mo;
                    continue;
                }
                int zz = 0;
                REP(c, 'A', 'Z') { //枚举这个位置所填的字母
                    if (c != A[i + j] && c != B[i + j]) { //如果发现这个字符一定不行 就留到最后一起处理
                        ++zz;
                        continue;
                    }
                    string s = now.s;
                    char r = '0'; //r代表这个位置可以是哪些串的结尾
                    if (c == A[i + j] && (check(s, j - 1, 1) || check(s, j, 1))) add(r, 1);
                    if (c == B[i + j] && (check(s, j - 1, 2) || check(s, j, 2))) add(r, 2);
                    s[j] = r;
                    node nxt(i, j, s);
                    if (S.find(nxt) == S.end())  //如果还没有这个状态就加进去
                        q.push(nxt);
                    S[nxt] = (S[nxt] + tmp) % mo;
                }
                string s = now.s;
                s[j] = '0'; 
                node nxt(i, j, s);
                if (S.find(nxt) == S.end()) 
                    q.push(nxt);
                S[nxt] = (S[nxt] + 1LL * tmp * zz % mo) % mo; //最后处理那些这个位置填0的串，优化常数
            }
			return ans;
		}
};

// CUT begin
ifstream data("StringPath.sample");

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

bool do_test(int n, int m, string A, string B, int __expected) {
    time_t startClock = clock();
    StringPath *instance = new StringPath();
    int __result = instance->countBoards(n, m, A, B);
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
        int n;
        from_stream(n);
        int m;
        from_stream(m);
        string A;
        from_stream(A);
        string B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477371921;
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
        cout << "StringPath (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
