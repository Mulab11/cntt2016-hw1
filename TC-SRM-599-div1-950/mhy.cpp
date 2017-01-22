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
class SimilarNames {
    public:
        int pre[105],tag[105];
        int a[105];
        int valid[1<<17],isvalid[1<<17];
        int dp[55][1<<17];
        vector<int> trans[1<<17];
        int count(vector<string> names, vector<int> info1, vector<int> info2) {
            int n=names.size(),m=info1.size();
            names.push_back(string(""));
            sort(names.begin(),names.end());
            for (int i=0;i<=n;i++){
                pre[i]=0;
                for (int j=1;j<i;j++) if (names[i].find(names[j])==0) pre[i]=j;
                //printf("%d %s %d\n",i,names[i].c_str(),pre[i]);
            }
            memset(tag,0,sizeof(tag));
            for (int i=0;i<m;i++) tag[info1[i]]=tag[info2[i]]=1;
            int q=0;
            for (int i=0;i<n;i++) if (tag[i]){
                a[q++]=i;
                //printf("%d\n",i);
            }
            int vc=0;
            for (int s=0;s<1<<q;s++){
                isvalid[s]=1;
                for (int j=0;j<m;j++){
                    int tag1=0,tag2=0;
                    for (int i=0;i<q;i++) if ((s>>i&1)&&a[i]==info1[j]) tag1=1;
                    for (int i=0;i<q;i++) if ((s>>i&1)&&a[i]==info2[j]) tag2=1;
                    if (tag1&&!tag2) isvalid[s]=0;
                }
                if (isvalid[s]) valid[vc++]=s;
            }
            for (int s=0;s<1<<q;s++) trans[s].clear();
            for (int s=0;s<1<<q;s++) if (isvalid[s]){
                //printf("%d\n",s);
                for (int i=s;;i=s&(i-1)){
                    if (isvalid[i]&&isvalid[s^i]){
                        trans[s].push_back(i);
                    }
                    if (!i) break;
                }
            }
            memset(dp,0,sizeof(dp));
            for (int i=0;i<=n;i++) dp[i][0]=1;
            for (int i=n;i;i--){
                for (int j=vc;j--;){
                    int s=valid[j];
                    for (int k=0;k<q;k++) if (~s>>k&1&&isvalid[s|1<<k]) dp[i][s|1<<k]=(dp[i][s|1<<k]+dp[i][s])%mod;
                }
                for (int j=vc;j--;){
                    int s=valid[j],sum=0;
                    for (int k=0;k<(int)trans[s].size();k++){
                        int ss=trans[s][k];
                        sum=(sum+1ll*dp[pre[i]][s^ss]*dp[i][ss])%mod;
                    }
                    dp[pre[i]][s]=sum;
                }
            }
            int ans=dp[0][(1<<q)-1];
            for (int i=n-q;i;i--) ans=1ll*ans*i%mod;
            return ans;
        }
};

// CUT begin
ifstream data("SimilarNames.sample");

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

bool do_test(vector<string> names, vector<int> info1, vector<int> info2, int __expected) {
    time_t startClock = clock();
    SimilarNames *instance = new SimilarNames();
    int __result = instance->count(names, info1, info2);
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
        vector<string> names;
        from_stream(names);
        vector<int> info1;
        from_stream(info1);
        vector<int> info2;
        from_stream(info2);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(names, info1, info2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483150853;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SimilarNames (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
