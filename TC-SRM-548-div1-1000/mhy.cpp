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

class KingdomAndCities {
    public:
        static const int mod=1000000007;
        inline long long qpow(long long x,int y){
            long long ans=1;
            for (;y;y>>=1,x=x*x%mod) if (y&1) ans=ans*x%mod;
            return ans;
        }
        int C[2505][2505];
        long long dp[55][55];
        int howMany(int n, int k, int m) {
            if (m<n-1) return 0;
            if (n==1) return k==0&&m==0;
            if (n==2) return k==0&&m==1;
            for (int i=0;i<=2500;*C[i++]=1) for (int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
            memset(dp,0,sizeof(dp));
            for (int i=1;i<=n;i++) for (int j=0;j<=m;j++){
                long long sum=C[C[i][2]][j];
                for (int k=1;k<i;k++) for (int l=0;l<=j;l++){
                    long long tmp=C[i-1][k-1]*dp[k][l]%mod*C[C[i-k][2]][j-l]%mod;
                    sum=(sum+mod-tmp)%mod;
                }
                dp[i][j]=sum;
            }
            if (k==0) return dp[n][m];
            if (k==1){
                long long ans=1ll*dp[n-1][m-2]*C[n-1][2]%mod;
                for (int i=1;i<n-1;i++) for (int j=0;j<=m-2;j++) ans=(ans+1ll*i%mod*(n-1-i)%mod*C[n-2][i-1]%mod*dp[i][j]%mod*dp[n-1-i][m-2-j])%mod;
                return int(ans);
            } else if (k==2){
                long long ans=1ll*dp[n-2][m-3]*(n-2)%mod*(n-2)%mod;
                for (int i=1;i<n-2;i++) for (int j=0;j<=m-3;j++) ans=(ans+2ll*i%mod*(n-2-i)%mod*C[n-3][i-1]%mod*dp[i][j]%mod*dp[n-2-i][m-3-j])%mod;
                if (m>=4){
                    ans=(ans+1ll*dp[n-2][m-4]*C[n-2][2]%mod*C[n-2][2])%mod;
                    for (int i=1;i<n-2;i++) for (int j=0;j<=m-4;j++)
                        ans=(ans+
                            (1ll*i%mod*i%mod*(n-2-i)%mod*(n-2-i)+2ll*i%mod*(n-2-i)%mod*(C[n-2-i][2]+C[i][2]))%mod*
                            C[n-3][i-1]%mod*dp[i][j]%mod*dp[n-2-i][m-4-j])%mod;
                    for (int x=1;x<n-2;x++) for (int y=1;x+y<n-2;y++){
                        int z=n-2-x-y;
                        for (int i=0;i<=m-4;i++) for (int j=0;i+j<=m-4;j++)
                            ans=(ans+1ll*C[n-3][x+y]*C[x+y][x]%mod*x%mod*y%mod*z%mod*(n-2)%mod*dp[x][i]%mod*dp[y][j]%mod*dp[z][m-4-i-j])%mod;
                    }
                }
                return ans;
            }
            return -1;
        }
};

// CUT begin
ifstream data("KingdomAndCities.sample");

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

bool do_test(int N, int M, int K, int __expected) {
    time_t startClock = clock();
    KingdomAndCities *instance = new KingdomAndCities();
    int __result = instance->howMany(N, M, K);
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
        int M;
        from_stream(M);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484325929;
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
        cout << "KingdomAndCities (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
