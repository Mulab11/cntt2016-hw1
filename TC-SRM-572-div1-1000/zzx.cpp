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
const int N = 1000;
int num[N], x[N], y[N];
char mp[N];                                            

class NextAndPrev {
    public: 
        int getMinimum(int nextCost, int prevCost, string S, string G) {
            if (S == G) return 0;
            int n = S.size();
            REP(c, 'a', 'z') num[c] = 0;
            REP(i, 0, n - 1) num[G[i]] = 1;
            int ok = 0;
            REP(c, 'a', 'z') if (!num[c]) ok = 1;
            if (!ok) return -1;
            REP(c, 'a', 'z') mp[c] = ' ';
            REP(i, 0, n - 1)
                if (mp[S[i]] == ' ') mp[S[i]] = G[i]; else
                    if (mp[S[i]] != G[i]) return -1;
            vector<pair<int, int> > x;
            x.clear();
            REP(c, 'a', 'z') 
                if (mp[c] != ' ')
                    x.PB(MP(c - 'a', mp[c] - 'a'));
            int m = x.size();
            int ans = mo * 2;
            REP(st, 0, m - 1) {
                int can = 1;
                REP(i, 0, m - 2) 
                    if (x[i].SC > x[i + 1].SC) can = 0;
                if (can) {
                    for (int shift=-1;shift<=2;shift++) {
                        for (int i=0;i<m;i++) x[i].SC += shift*26;
                        int i = 0, cur = 0;
                        while (i < m) {
                            int j = i;
                            while (j < m && x[i].SC == x[j].SC) j++;
                            int low = x[i].SC, high = x[i].SC;
                            for (int k=i;k<j;k++) {
                                if (x[k].first < low) low = x[k].first;
                                if (x[k].first > high) high = x[k].first;
                            }
                            cur += (x[i].SC-low)*nextCost;
                            cur += (high-x[i].SC)*prevCost;
                            i = j;
                        }
                        if (cur < ans) ans = cur;
                        for (int i=0;i<m;i++) x[i].SC -= shift*26;
                    }
                }
                x[0].first += 26;
                sort(x.begin(), x.end());
            }
            return ans > 1e9 ? -1 : ans;
        }
};

// CUT begin
ifstream data("NextAndPrev.sample");

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

bool do_test(int nextCost, int prevCost, string S, string G, int __expected) {
    time_t SClock = clock();
    NextAndPrev *instance = new NextAndPrev();
    int __result = instance->getMinimum(nextCost, prevCost, S, G);
    double elapsed = (double)(clock() - SClock) / CLOCKS_PER_SEC;
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
        int nextCost;
        from_stream(nextCost);
        int prevCost;
        from_stream(prevCost);
        string S;
        from_stream(S);
        string G;
        from_stream(G);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(nextCost, prevCost, S, G, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1481876695;
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
        cout << "NextAndPrev (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
