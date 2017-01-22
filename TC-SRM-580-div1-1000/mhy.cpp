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

template <typename T> inline void tension(T &a,const T &b){if (a>b) a=b;}
template <typename T> inline void relax(T &a,const T &b){if (a<b) a=b;}

class WallGameDiv1 {
    public:
        int n,m;
        int dp[55][55][55][2];
        int a[55][55];
        int sum[55][55];
        int DP(int i,int l,int r,int sgn){
            if (i==n-1) return a[i][l];
            int &ans=dp[i][l][r][sgn];
            if (~ans) return ans;
            int j=sgn?r:l;
            ans=a[i][j]+DP(i+1,j,j,0);
            if (r-l==m-1) return ans;
            int v=0x3f3f3f3f;
            if (l>0) tension(v,sum[i][j]-sum[i][l-1]+DP(i,l-1,r,0));
            if (r<m-1) tension(v,sum[i][r]-(j?sum[i][j-1]:0)+DP(i,l,r+1,1));
            relax(ans,v);
            return ans;
        }
        int play(vector<string> costs){
            memset(dp,-1,sizeof(dp));
            n=costs.size(),m=costs[0].size();
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) sum[i][j]=(j?sum[i][j-1]:0)+(a[i][j]=costs[i][j]-'0');
            int ans=0x3f3f3f3f;
            for (int j=0;j<m;j++) tension(ans,DP(0,j,j,0));
            return ans;
        }
};

// CUT begin
ifstream data("WallGameDiv1.sample");

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

bool do_test(vector<string> costs, int __expected) {
    time_t startClock = clock();
    WallGameDiv1 *instance = new WallGameDiv1();
    int __result = instance->play(costs);
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
        vector<string> costs;
        from_stream(costs);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(costs, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475717647;
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
        cout << "WallGameDiv1 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
            /*
            for (int i=0;i<m;i++) dp[0][i][i][0]=costs[0][i]-'0';
            for (int i=0;i<n-1;i++){
                for (int j=0;j<m;j++) dp[i][j][j][1]=dp[i][j][j][0];
                for (int j=0;j<m;j++) dp[i+1][j][j][0]=0;
                sum[0]=costs[i][0]-'0';for (int j=1;j<m;j++) sum[j]=sum[j-1]+costs[i][j]-'0';
                for (int len=0;len<m;len++) for (int l=0,r=len;r<m;l++,r++){
                    //printf("%d %d %d %d %d\n",i,l,r,dp[i][l][r][0],dp[i][l][r][1]);
                    if (l>0) tension(dp[i][l-1][r][0],dp[i][l][r][0]+query(l-1,l-1));
                    if (l>0) tension(dp[i][l-1][r][0],dp[i][l][r][1]+query(l-1,r-1));
                    if (r<m-1) tension(dp[i][l][r+1][1],dp[i][l][r][0]+query(l+1,r));
                    if (r<m-1) tension(dp[i][l][r+1][1],dp[i][l][r][1]+query(r+1,r+1));
                    relax(dp[i+1][l][l][0],dp[i][l][r][0]+costs[i+1][l]-'0');
                    relax(dp[i+1][r][r][0],dp[i][l][r][1]+costs[i+1][r]-'0');
                }
            }
            */


// CUT end
