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

const int mod=1000000009;
inline void add(long long &a,long long b){a=(a+b)%mod;}

class TheExperiment {
    public:
        int sum[305];
        long long dp[305][305][3];
        int countPlacements(vector<string> intensity, int m, int q, int L, int R) {
            memset(dp,0,sizeof(dp));
            string str;
            for (int i=0;i<(int)intensity.size();i++) str+=intensity[i];
            int n=str.size();
            sum[0]=0;for (int i=1;i<=n;i++) sum[i]=sum[i-1]+str[i-1]-'0';
            dp[0][0][0]=1;
            for (int i=0;i<n;i++) for (int j=0;j<=m;j++){
                if (dp[i][j][0]){
                    add(dp[i+1][j][0],dp[i][j][0]);
                    if (j<m){
                        for (int k=1;k<=q&&i+k<=n;k++) if (L<=sum[i+k]-sum[i]&&sum[i+k]-sum[i]<=R) add(dp[i+k][j+1][k<q?1:2],dp[i][j][0]);
                    }
                }
                if (dp[i][j][1]){
                    if (j<m){
                        for (int k=1;k<=q&&i+k<=n;k++) if (L<=sum[i+k]-sum[i]&&sum[i+k]-sum[i]<=R) add(dp[i+k][j+1][k<q?1:2],dp[i][j][1]);
                    }
                }
                if (dp[i][j][2]){
                    add(dp[i+1][j][0],dp[i][j][2]);
                    if (j<m){
                        for (int k=1;k<=q&&i+k<=n;k++) if (L<=sum[i+k]-sum[i]&&sum[i+k]-sum[i]<=R) add(dp[i+k][j+1][2],dp[i][j][2]);
                    }
                }
            }
            return (dp[n][m][0]+dp[n][m][2])%mod;
        }
};

// CUT begin
ifstream data("TheExperiment.sample");

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

bool do_test(vector<string> intensity, int M, int L, int A, int B, int __expected) {
    time_t startClock = clock();
    TheExperiment *instance = new TheExperiment();
    int __result = instance->countPlacements(intensity, M, L, A, B);
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
        vector<string> intensity;
        from_stream(intensity);
        int M;
        from_stream(M);
        int L;
        from_stream(L);
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(intensity, M, L, A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476888835;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 576 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheExperiment (576 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
