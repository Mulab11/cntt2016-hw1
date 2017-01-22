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

class LittleElephantAndPermutationDiv1 {
    public:
        static const int mod=1000000007;
        inline void add(int &a,long long b){a=(a+b)%mod;}
        int dp[55][55][2505];
        int getNumber(int n, int m) {
            memset(dp,0,sizeof(dp));
            dp[0][0][0]=1;
            for (int i=1;i<=n;i++) for (int j=0;j<i;j++) for (int k=0;k<=n*n;k++) if (dp[i-1][j][k]){
                long long x=dp[i-1][j][k];
                add(dp[i][j][k+i],x);
                if (j) add(dp[i][j-1][k+2*i],x*j*j);
                if (j) add(dp[i][j][k+i],x*j);
                if (j) add(dp[i][j][k+i],x*j);
                add(dp[i][j+1][k],x);
                //if (n==3) printf("%d %d %d %d\n",i-1,j,k,x);
            }
            int ans=0;
            for (int i=m;i<=n*n;i++) add(ans,dp[n][0][i]);
            for (int i=1;i<=n;i++) ans=1ll*ans*i%mod;
            return ans;
        }
};

// CUT begin
ifstream data("LittleElephantAndPermutationDiv1.sample");

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

bool do_test(int N, int K, int __expected) {
    time_t startClock = clock();
    LittleElephantAndPermutationDiv1 *instance = new LittleElephantAndPermutationDiv1();
    int __result = instance->getNumber(N, K);
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
        int N;
        from_stream(N);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484059901;
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
        cout << "LittleElephantAndPermutationDiv1 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
