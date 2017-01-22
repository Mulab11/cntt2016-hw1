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

const int mod=1000000007;
inline long long inverse(long long x){
    long long ans=1;
    for (int y=mod-2;y;y>>=1,x=x*x%mod) if (y&1) ans=ans*x%mod;
    return ans;
}

class LISNumber {
    public:
        long long fact[100005],ifact[100005];
        inline long long C(int n,int m){return n>m?fact[n]*ifact[n-m]%mod*ifact[m]%mod:n==m;}
        void init(int n=100000){
            *fact=1;for (int i=1;i<=n;i++) fact[i]=fact[i-1]*i%mod;
            ifact[n]=inverse(fact[n]);for (int i=n;i;i--) ifact[i-1]=ifact[i]*i%mod;
        }
        long long dp[2005][2005];
        int cnt[2005];
        int count(vector<int> cardsnum, int m) {
            init();
            int n=cardsnum.size();
            memset(cnt,0,sizeof(cnt));
            for (int i=n;i--;) cnt[i]=cnt[i+1]+cardsnum[i];
            memset(dp,0,sizeof(dp));
            dp[n][0]=1;
            for (int i=n;i--;) for (int j=0;j<=m;j++) if (dp[i+1][j]) for (int k=0;k<=j;k++){
                int now=cardsnum[i]-k;
                if (now<0) continue;
                long long sum=dp[i+1][j]*C(j,k)%mod;
                int ways=cnt[i+1]+1-j+k;
                (dp[i][j+now]+=sum*C(now+ways-1,now))%=mod;
            }
            return dp[0][m];
        }
};

// CUT begin
ifstream data("LISNumber.sample");

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

bool do_test(vector<int> cardsnum, int K, int __expected) {
    time_t startClock = clock();
    LISNumber *instance = new LISNumber();
    int __result = instance->count(cardsnum, K);
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
        vector<int> cardsnum;
        from_stream(cardsnum);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(cardsnum, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475502943;
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
        cout << "LISNumber (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
