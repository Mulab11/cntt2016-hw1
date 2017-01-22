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

class LittleElephantAndRGB {
    public:
        long long dp[2505][2505],s[2505];
        long long getNumber(vector<string> list, int m) {
            memset(dp,0,sizeof(dp)),memset(s,0,sizeof(s));
            string str="?";
            for (int i=0;i<(int)list.size();i++) str+=list[i];
            int n=str.size()-1;
            //printf("%d\n",n);
            dp[0][0]=1;
            for (int i=1;i<=n;i++){
                //if (str[i]=='G') for (int j=1;j<=n;j++) dp[i][j]=dp[i-1][j-1];
                if (1){
                    int tag=1;
                    for (int j=i,c=0,cc=-1;j;j--){
                        if (str[j]=='G') c++; else{
                            if (cc<0) cc=c;
                            c=0;
                        }
                        if (c==m) tag=0;
                        dp[i][cc<0?c:cc]+=tag;
                    }
                }
                for (int j=m;j<=n;j++) dp[i][j]=0;
                for (int j=m-1;~j;j--) dp[i][j]+=dp[i][j+1];
                //for (int j=0;j<=n;j++) dp[i][j]+=dp[i-1][j];
                //for (int j=0;j<=n;j++) if (dp[i][j]) printf("%d %d %lld\n",i,j,dp[i][j]);
            }
            for (int i=1;i<=n;i++){
                for (int j=0;j<=n;j++) dp[i][j]+=dp[i-1][j];
            }
            for (int i=1;i<=n;i++){
                s[i]=s[i-1];
                for (int j=i,tag=0,c=0;j;j--){
                    if (str[j]=='G') c++; else c=0;
                    if (c==m) tag=1;
                    s[i]+=tag;
                }
            }
            long long ans=0;
            for (int i=1;i<=n;i++) for (int j=i,tag=0,c=0,cc=-1;j<=n;j++){
                if (str[j]=='G') c++; else{
                    if (cc<0) cc=c;
                    c=0;
                }
                if (c==m) tag=1;
                if (tag){
                    ans+=i*(i-1ll)>>1;
                    //printf("%d-%d %lld\n",i,j,i*(i-1ll)>>1);
                } else{
                    int t=cc<0?c:cc;
                    ans+=(t?dp[i-1][m-t]:0)+s[i-1];
                    //printf("%d %d %d %lld %lld\n",i,j,t,(t?dp[i-1][m-t]:0),s[i-1]);
                }
            }
            return ans;
        }
};

// CUT begin
ifstream data("LittleElephantAndRGB.sample");

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

bool do_test(vector<string> list, int minGreen, long long __expected) {
    time_t startClock = clock();
    LittleElephantAndRGB *instance = new LittleElephantAndRGB();
    long long __result = instance->getNumber(list, minGreen);
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
        vector<string> list;
        from_stream(list);
        int minGreen;
        from_stream(minGreen);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(list, minGreen, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483803669;
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
        cout << "LittleElephantAndRGB (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
