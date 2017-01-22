#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

class StringPath {
    public:
        static const int mod=1000000009;
        inline void inc(int &a,int b){if ((a+=b)>=mod) a-=mod;}
        int dp[10][10][1<<8][1<<8];
        string a,b;
        int n,m;
        inline int change(int s,int i,int x){
            if (x&&((i&&(s>>(i-1)&1))||(s>>i&1))) return s|(1<<i); else return s-(s&(1<<i));
        }
        int DP(int x,int y,int sx,int sy){
            int &ans=dp[x][y][sx][sy];
            if (~ans) return ans;
            if (x==n)
                ans=(sx&(1<<(m-1)))&&(sy&(1<<(m-1)));
            else if (y==m)
                ans=DP(x+1,0,sx,sy);
            else{
                ans=0;
                for (char c='A';c<='Z';c++) inc(ans,DP(x,y+1,change(sx,y,a[x+y]==c),change(sy,y,b[x+y]==c)));
            }
            return ans;
        }
        int countBoards(int _n, int _m, string _a, string _b) {
            memset(dp,-1,sizeof(dp));
            n=_n,m=_m,a=_a,b=_b;
            return DP(0,0,1,1);
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
        int T = time(NULL) - 1475717512;
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
