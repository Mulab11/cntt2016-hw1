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
inline void inc(int &a,int b){if ((a+=b)>=mod) a-=mod;}

class GooseInZooDivOne {
    public:
        int fa[10005],size[10005];
        inline int find(int i){return fa[i]!=i?fa[i]=find(fa[i]):i;}
        inline void merge(int x,int y){if ((x=find(x))!=(y=find(y))) size[fa[y]=x]+=size[y];}
        int id[105][105];
        int dp[2];
        int count(vector<string> field, int dist) {
            int n=field.size(),m=field[0].size(),V=0;
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) if (field[i][j]=='v') id[i][j]=++V; else id[i][j]=0;
            for (int i=1;i<=V;i++) size[fa[i]=i]=1;
            for (int i=0;i<n;i++) for (int j=0;j<m;j++) for (int k=0;k<n;k++) for (int l=0;l<m;l++) if (id[i][j]&&id[k][l]&&abs(i-k)+abs(j-l)<=dist) merge(id[i][j],id[k][l]);
            dp[0]=1,dp[1]=0;
            for (int i=1;i<=V;i++) if (find(i)==i){
                int f0=dp[0],f1=dp[1];
                inc(dp[size[i]&1],f0),inc(dp[~size[i]&1],f1);
            }
            return (dp[0]+mod-1)%mod;
        }
};

// CUT begin
ifstream data("GooseInZooDivOne.sample");

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

bool do_test(vector<string> field, int dist, int __expected) {
    time_t startClock = clock();
    GooseInZooDivOne *instance = new GooseInZooDivOne();
    int __result = instance->count(field, dist);
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
        vector<string> field;
        from_stream(field);
        int dist;
        from_stream(dist);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, dist, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475574803;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "GooseInZooDivOne (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
