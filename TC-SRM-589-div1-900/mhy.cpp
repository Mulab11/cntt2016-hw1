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

class FlippingBitsDiv1 {
    public:
        int bit[305],dp[305][2];
        int cnt[305][2];
        int getmin(vector<string> S, int m) {
            string str;
            for (int i=0;i<(int)S.size();i++) str=str+S[i];
            int n=str.size();
            if (n<m) return 0;
            if (m<=17){
                int ans=0x3f3f3f3f;
                for (int s=0;s<1<<m;s++){
                    for (int i=0;i<m;i++) bit[i]=s>>i&1;
                    memset(dp,0x3f,sizeof(dp));
                    dp[0][0]=dp[0][1]=1;
                    for (int i=1,l=0,r=m-1;l<n;i++,l=r+1,r=l+m-1){
                        if (r>=n) r=n-1;
                        int f0=0;
                        for (int j=l;j<=r;j++) if (str[j]-'0'!=bit[j-l]) f0++;
                        int f1=r-l+1-f0;
                        dp[i][0]=min(dp[i-1][0]+f0,dp[i-1][1]+f0+1);
                        dp[i][1]=min(dp[i-1][1]+f1,dp[i-1][0]+f1+1);
                    }
                    ans=min(ans,dp[(n+m-1)/m][0]-1);
                    if (n%m==0) ans=min(ans,dp[n/m][1]);
                }
                return ans;
            } else{
                int ans=0x3f3f3f3f;
                int q=(n+m-1)/m;
                for (int s=0;s<1<<q;s++){
                    if (n%m!=0&&s>>(q-1)&1) continue;
                    memset(cnt,0,sizeof(cnt));
                    int sum=1;
                    for (int i=0,l=0,r=m-1;l<n;i++,l=r+1,r=l+m-1){
                        if (r>=n) r=n-1;
                        if (i&&(s>>(i-1)&1)!=(s>>i&1)) sum++;
                        if (~s>>i&1){
                            for (int j=l;j<=r;j++) cnt[j-l][str[j]-'0']++;
                        } else{
                            for (int j=l;j<=r;j++) cnt[j-l][!(str[j]-'0')]++;
                        }
                    }
                    if (~s>>(q-1)&1) sum--;
                    for (int i=0;i<m;i++) sum+=min(cnt[i][0],cnt[i][1]);
                    ans=min(ans,sum);
                }
                return ans;
            }
        }
};

// CUT begin
ifstream data("FlippingBitsDiv1.sample");

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

bool do_test(vector<string> S, int M, int __expected) {
    time_t startClock = clock();
    FlippingBitsDiv1 *instance = new FlippingBitsDiv1();
    int __result = instance->getmin(S, M);
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
        vector<string> S;
        from_stream(S);
        int M;
        from_stream(M);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475495365;
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
        cout << "FlippingBitsDiv1 (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
