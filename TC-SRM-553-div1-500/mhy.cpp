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

class TwoConvexShapes {
    public:
        static const int mod=1000000007;
        int dp[4][55][55];
        int countWays(vector<string> grid) {
            int n=grid.size(),m=grid[0].size(),ans=0;
            //printf("%d %d\n",n,m);
            for (int i=0;i<n;i++) for (int j=0;j<=m;j++){
                dp[0][i][j]=0;
                int tag=1;
                for (int k=0;k<j;k++) if (grid[i][k]=='W') tag=0;for (int k=j;k<m;k++) if (grid[i][k]=='B') tag=0;
                if (!tag) continue;
                if (i) for (int k=0;k<=j;k++) (dp[0][i][j]+=dp[0][i-1][k])%=mod; else dp[0][i][j]=1;
                if (i==n-1&&j) (ans+=dp[0][i][j])%=mod;
                //if (tag) printf("%d %d %d\n",i,j,dp[0][i][j]);
            }
            for (int i=0;i<n;i++) for (int j=0;j<=m;j++){
                dp[1][i][j]=0;
                int tag=1;
                for (int k=0;k<j;k++) if (grid[i][k]=='W') tag=0;for (int k=j;k<m;k++) if (grid[i][k]=='B') tag=0;
                if (!tag) continue;
                if (i) for (int k=j;k<=m;k++) (dp[1][i][j]+=dp[1][i-1][k])%=mod; else dp[1][i][j]=1;
                if (i==n-1&&j<m) (ans+=dp[1][i][j])%=mod;
            }
            for (int i=0;i<n;i++) for (int j=0;j<=m;j++){
                dp[2][i][j]=0;
                int tag=1;
                for (int k=0;k<j;k++) if (grid[i][k]=='B') tag=0;for (int k=j;k<m;k++) if (grid[i][k]=='W') tag=0;
                if (!tag) continue;
                if (i) for (int k=0;k<=j;k++) (dp[2][i][j]+=dp[2][i-1][k])%=mod; else dp[2][i][j]=1;
                if (i==n-1&&j) (ans+=dp[2][i][j])%=mod;
            }
            for (int i=0;i<n;i++) for (int j=0;j<=m;j++){
                dp[3][i][j]=0;
                int tag=1;
                for (int k=0;k<j;k++) if (grid[i][k]=='B') tag=0;for (int k=j;k<m;k++) if (grid[i][k]=='W') tag=0;
                if (!tag) continue;
                if (i) for (int k=j;k<=m;k++) (dp[3][i][j]+=dp[3][i-1][k])%=mod; else dp[3][i][j]=1;
                if (i==n-1&&j<m) (ans+=dp[3][i][j])%=mod;
            }
            //for (int f=0;f<4;f++) for (int i=0;i<n;i++) for (int j=0;j<m;j++) (ans+=dp[f][i][j])%=mod;
            //for (int f=0;f<4;f++) for (int i=0;i<n;i++) for (int j=0;j<m;j++) printf("%d %d %d %d\n",f,i,j,dp[f][i][j]);
            for (int i=0;i<n;i++){
                int tag=1;
                for (int j=0;j<=i;j++) for (int k=0;k<m;k++) if (grid[j][k]=='W') tag=0;
                for (int j=i+1;j<n;j++) for (int k=0;k<m;k++) if (grid[j][k]=='B') tag=0;
                ans-=tag;
            }
            for (int i=0;i<n;i++){
                int tag=1;
                for (int j=0;j<=i;j++) for (int k=0;k<m;k++) if (grid[j][k]=='B') tag=0;
                for (int j=i+1;j<n;j++) for (int k=0;k<m;k++) if (grid[j][k]=='W') tag=0;
                ans-=tag;
            }
            for (int i=0;i<m;i++){
                int tag=1;
                for (int j=0;j<n;j++) for (int k=0;k<=i;k++) if (grid[j][k]=='W') tag=0;
                for (int j=0;j<n;j++) for (int k=i+1;k<m;k++) if (grid[j][k]=='B') tag=0;
                ans-=tag;
            }
            for (int i=0;i<m;i++){
                int tag=1;
                for (int j=0;j<n;j++) for (int k=0;k<=i;k++) if (grid[j][k]=='B') tag=0;
                for (int j=0;j<n;j++) for (int k=i+1;k<m;k++) if (grid[j][k]=='W') tag=0;
                ans-=tag;
            }
            {
                int tag=1;
                for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (grid[i][j]=='W') tag=0;
                ans+=tag;
            }
            {
                int tag=1;
                for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (grid[i][j]=='B') tag=0;
                ans+=tag;
            }
            return ans;
        }
};

// CUT begin
ifstream data("TwoConvexShapes.sample");

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

bool do_test(vector<string> grid, int __expected) {
    time_t startClock = clock();
    TwoConvexShapes *instance = new TwoConvexShapes();
    int __result = instance->countWays(grid);
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
        vector<string> grid;
        from_stream(grid);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(grid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483456356;
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
        cout << "TwoConvexShapes (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
