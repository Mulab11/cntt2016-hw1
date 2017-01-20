/* CopyR 2016 AareaTheSky */
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
const int M = 70000;
PII A[12 * M]; //所有的点
LL l[12 * M], r[12 * M];
LL s[12 * M];
struct Vector {
    LL x, y;
    Vector() {}
    Vector(const int &_x, const int &_y) :
        x(_x), y(_y) {}
    Vector operator + (const Vector &b) {
        return Vector(x + b.x, y + b.y);
    }
    Vector operator - (const Vector &b) {
        return Vector(x - b.x, y - b.y);
    }
};

typedef Vector Point;
LL area(const Vector & a, const Vector & b, const Vector & c) { //计算叉积
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<int> X, Y;
bool check(PII A, PII B) { //判断线段AB 是否能作为Triangle的边
    Vector a(A.FR, A.SC), b(B.FR, B.SC);
    for (int i = 0; i < X.size(); ++i) { 
        if (area(a, b, Vector(X[i], Y[i])) < 0)
            return false;
    }
    return true;
}

class EnclosingTriangle {
    public:
        long long getNumber(int m, vector<int> x, vector<int> y) {
            int n = 0;
            int i, j, k;
            X = x;
            Y = y;
            REP(i, 0, m) A[n++] = MP(0, i);
            REP(i, 1, m) A[n++] = MP(i, m);
            PER(i, m - 1, 0) A[n++] = MP(m, i);
            PER(i, m - 1, 1) A[n++] = MP(i, 0);
            REP(i, 0, n - 1) A[i + n] = A[i], A[i + 2 * n] = A[i]; //把边界上的点复制成3份这样方便进行处理

            REP(i, n, 2 * n - 1) { //从中间开始处理
                int L, R;
                L = i - n + 1;
                R = i - 1;
                while (R > L) { //二分得到每个点的左边能看到的最远的点
                    int mid = (L + R) >> 1;
                    if (check(A[i], A[mid])) R = mid;
                    else L = mid + 1;
                }
                l[i] = l[i - n] = l[i + n] = i - R;

                L = i + n - 1;
                R = i + 1;

                while (L > R) { //二分得到每个点的右边能看到的最远的点
                    int mid = (L + R + 1) >> 1;
                    if (check(A[mid], A[i]))    R = mid;
                    else L = mid - 1;
                }
                r[i] = r[i - n] = r[i + n] = R - i;
            }
            s[0] = r[0];
            REP(i, 1, 3 * n - 1) s[i] = r[i] + s[i - 1]; //对r[i]求前缀和

            LL ans = 0;
            REP(i, n, 2 * n - 1) { //枚举第一个点
                int c = i - l[i];
                int L = c - l[c] + n;
                if (L == i) L++;
                int R = i + r[i];

                if (R < L) continue;
                ans += s[R] - s[L - 1]; //把所有可行的B全都加起来
                ans -= 1LL * (c + n - R + c + n - L - 2) * (R - L + 1) / 2; //等差数列求和

                if (R == c + n) ans--; //边界情况需要考虑
                if (r[i] + r[R] == n) ans--;
            }
            return ans / 3;//每个三角形被计算了三次
        }
};
// CUT begin
ifstream data("EnclosingTriangle.sample");

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

bool do_test(int m, vector<int> x, vector<int> y, long long __expected) {
    time_t startClock = clock();
    EnclosingTriangle *instance = new EnclosingTriangle();
    long long __result = instance->getNumber(m, x, y);
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
        int m;
        from_stream(m);
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(m, x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477039125;
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
        cout << "EnclosingTriangle (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
