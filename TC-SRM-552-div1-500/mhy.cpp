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

template <typename T> inline void relax(T &a,const T &b){if (a<b) a=b;}

class FoxAndFlowerShopDivOne {
    public:
        int s[105][105],sum[105][105];
        inline int calc(int s[105][105],int x1,int y1,int x2,int y2){
            return s[x2][y2]-(x1?s[x1-1][y2]:0)-(y1?s[x2][y1-1]:0)+(x1&&y1?s[x1-1][y1-1]:0);
        }
        int _[10005],prefix[105][2005],suffix[105][2005];
        int theMaxFlowers(vector<string> flowers, int q) {
            int n=flowers.size(),m=flowers[0].size(),ans=-0x3f3f3f3f;
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) s[i][j]=(i?s[i-1][j]:0)+(j?s[i][j-1]:0)+(flowers[i][j]!='.'?flowers[i][j]=='L'?1:-1:0)-(i&&j?s[i-1][j-1]:0);
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) sum[i][j]=(i?sum[i-1][j]:0)+(j?sum[i][j-1]:0)+(flowers[i][j]!='.')-(i&&j?sum[i-1][j-1]:0);
            memset(prefix,0,sizeof(prefix)),memset(suffix,0,sizeof(suffix));
            for (int i=0;i<n;i++){
                for (int _=-n*m;_<=n*m;_++) prefix[i][_]=i?prefix[i-1][_]:-0x3f3f3f3f;
                for (int j=0;j<m;j++) for (int k=0;k<n;k++) for (int l=0;l<m;l++) if (k<=i&&l<=j) relax(prefix[i][calc(s,k,l,i,j)],calc(sum,k,l,i,j));
            }
            for (int k=n;k--;){
                for (int _=-n*m;_<=n*m;_++) suffix[k][_]=k+1<n?suffix[k+1][_]:-0x3f3f3f3f;
                for (int l=0;l<m;l++) for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (k<=i&&l<=j) relax(suffix[k][calc(s,k,l,i,j)],calc(sum,k,l,i,j));
            }
            for (int i=1;i<n;i++) for (int j=-n*m;j<=n*m;j++) for (int k=-q-j;k<=q-j;k++) if (-n*m<=k&&k<=n*m) ans=max(ans,prefix[i-1][j]+suffix[i][k]);
            memset(prefix,0,sizeof(prefix)),memset(suffix,0,sizeof(suffix));
            for (int j=0;j<m;j++){
                for (int _=-n*m;_<=n*m;_++) prefix[j][_]=j?prefix[j-1][_]:-0x3f3f3f3f;
                for (int i=0;i<n;i++) for (int k=0;k<n;k++) for (int l=0;l<m;l++) if (k<=i&&l<=j) relax(prefix[j][calc(s,k,l,i,j)],calc(sum,k,l,i,j));
            }
            for (int l=m;l--;){
                for (int _=-n*m;_<=n*m;_++) suffix[l][_]=l+1<m?suffix[l+1][_]:-0x3f3f3f3f;
                for (int k=0;k<n;k++) for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (k<=i&&l<=j) relax(suffix[l][calc(s,k,l,i,j)],calc(sum,k,l,i,j));
            }
            for (int i=1;i<m;i++) for (int j=-n*m;j<=n*m;j++) for (int k=-q-j;k<=q-j;k++) if (-n*m<=k&&k<=n*m) ans=max(ans,prefix[i-1][j]+suffix[i][k]);
            if (ans<-1) ans=-1;
            return ans;
        }
};

// CUT begin
ifstream data("FoxAndFlowerShopDivOne.sample");

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

bool do_test(vector<string> flowers, int maxDiff, int __expected) {
    time_t startClock = clock();
    FoxAndFlowerShopDivOne *instance = new FoxAndFlowerShopDivOne();
    int __result = instance->theMaxFlowers(flowers, maxDiff);
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
        vector<string> flowers;
        from_stream(flowers);
        int maxDiff;
        from_stream(maxDiff);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(flowers, maxDiff, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483287340;
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
        cout << "FoxAndFlowerShopDivOne (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
