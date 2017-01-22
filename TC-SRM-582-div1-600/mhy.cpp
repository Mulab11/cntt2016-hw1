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

class ColorfulBuilding {
    public:
        static const int mod=1000000009;
        inline long long inverse(long long x){
            long long ans=1;
            for (int y=mod-2;y;y>>=1,x=x*x%mod) if (y&1) ans=ans*x%mod;
            return ans;
        }
        int tag[65536];
        int c[2005];
        long long fact[2005],ifact[2005];
        long long dp[1305][1305],sum[1305],ss[1305][1305];
        int count(vector<string> color1, vector<string> color2, int L) {
            memset(tag,0,sizeof(tag));
            memset(dp,0,sizeof(dp)),memset(sum,0,sizeof(sum)),memset(ss,0,sizeof(ss));
            *fact=1;for (int i=1;i<=2000;i++) fact[i]=fact[i-1]*i%mod;
            ifact[2000]=inverse(fact[2000]);for (int i=2000;i;i--) ifact[i-1]=ifact[i]*i%mod;
            string c1,c2;
            for (int i=0;i<(int)color1.size();i++) c1+=color1[i];
            for (int i=0;i<(int)color2.size();i++) c2+=color2[i];
            int n=c1.size();
            for (int i=0,t=0;i<n;i++){
                int &x=tag[256*c1[i]+c2[i]];
                if (!x) x=++t;
                c[i+1]=x;
                //printf("%d %d\n",i,x);
            }
            for (int i=1;i<=n;i++){
                dp[i][1]=(fact[n-1]+ss[c[i]][1])%mod;
                for (int j=2;j<=i;j++) dp[i][j]=(sum[j-1]+mod-ss[c[i]][j-1]+ss[c[i]][j])%mod;
                if (i<n) for (int j=1;j<=i;j++) ss[c[i]][j]=(ss[c[i]][j]+dp[i][j]*fact[n-i-1]%mod*ifact[n-i])%mod,sum[j]=(sum[j]+dp[i][j]*fact[n-i-1]%mod*ifact[n-i])%mod;
            }
            return int(dp[n][L]);
        }
};

// CUT begin
ifstream data("ColorfulBuilding.sample");

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

bool do_test(vector<string> color1, vector<string> color2, int L, int __expected) {
    time_t startClock = clock();
    ColorfulBuilding *instance = new ColorfulBuilding();
    int __result = instance->count(color1, color2, L);
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
        vector<string> color1;
        from_stream(color1);
        vector<string> color2;
        from_stream(color2);
        int L;
        from_stream(L);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(color1, color2, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483456404;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ColorfulBuilding (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
