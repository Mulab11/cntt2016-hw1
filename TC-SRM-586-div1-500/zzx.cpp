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
#include <iterator>
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
/*
 * A shortest path model
 * we assume that there is a standard year and the deviation of dynasty i is xi
 * we can obtain some inequalities 
 * we can run a floyd and solve this system
 */
const int N = 33;
const int inf = 1e9;
int dis[N][N], n;
string tmp;
vector<vector<int> > d(n);
void READ(vector<string> DY, vector<string> BA, vector<string> Q) {
    d.resize(n);
    d.clear();
    for(int i = 0; i < n; ++i) {
        istringstream iss(DY[i]);
        copy(istream_iterator<int>(iss), istream_iterator<int>(), back_inserter(d[i]));
    }
    REP(i, 0, n - 1) REP(j, 0, n - 1) dis[i][j] = inf;
    string in = "";
    for(int i = 0; i < BA.size(); ++i) in += BA[i];
    istringstream iss(in);
    tmp = "";
    while(iss >> tmp) {
        int date1, date2, year1, year2;
        date1 = tmp[0] - 'A';
        year1 = tmp[1] - '0';
        date2 = tmp[3] - 'A';
        year2 = tmp[4] - '0';
        int le1 = d[date1][year1], ri1 = d[date1][year1 + 1] - 1;
        int le2 = d[date2][year2], ri2 = d[date2][year2 + 1] - 1;
        dis[date1][date2] = min(dis[date1][date2], ri2 - le1);
        dis[date2][date1] = min(dis[date2][date1], ri1 - le2);
    }
}
class History {
    public:
        string verifyClaims(vector <string> DY, vector <string> BA, vector <string> Q) {
            n = DY.size();
            READ(DY, BA, Q);
            /*
             * floyd
             */
            REP(k, 0, n - 1) 
                REP(i, 0, n - 1)
                    REP(j, 0, n - 1) 
                if(dis[i][k] != inf && dis[k][j] != inf && dis[i][k] + dis[k][j] < dis[i][j]) dis[i][j] = dis[i][k] + dis[k][j];
            string res = "";
            for(int i = 0; i < Q.size(); ++i) {
                int date1, date2, year1, year2;
                tmp = Q[i];
                date1 = tmp[0] - 'A';
                year1 = tmp[1] - '0';
                date2 = tmp[3] - 'A';
                year2 = tmp[4] - '0';
                int le1 = d[date1][year1], ri1 = d[date1][year1 + 1] - 1;
                int le2 = d[date2][year2], ri2 = d[date2][year2 + 1] - 1;
                int le = max(le2 - ri1, -dis[date2][date1]), ri = min(ri2 - le1, dis[date1][date2]);
                if(le <= ri) {
                    res += 'Y';
                } else {
                    res += 'N';
                }
            }
            return res;
        }
};

// CUT begin
ifstream data("History.sample");

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

bool do_test(vector<string> DY, vector<string> BA, vector<string> Q, string __expected) {
    time_t startClock = clock();
    History *instance = new History();
    string __result = instance->verifyClaims(DY, BA, Q);
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
        vector<string> DY;
        from_stream(DY);
        vector<string> BA;
        from_stream(BA);
        vector<string> Q;
        from_stream(Q);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(DY, BA, Q, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484129414;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "History (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
