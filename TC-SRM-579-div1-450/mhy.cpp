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

template <typename T> inline void tension(T &a, const T &b){if (a>b) a=b;}

class TravellingPurchasingMan {
    public:
        int popcount[1<<17];
        int dist[55][55];
        int l[55],r[55],t[55];
        int dp[1<<17][17];
        int maxStores(int n, vector<string> interestingStores, vector<string> roads) {
            memset(dist,0x3f,sizeof(dist));
            for (int i=0;i<n;i++) dist[i][i]=0;
            int m=interestingStores.size();
            for (int i=0;i<m;i++){
                istringstream s(interestingStores[i]);
                s>>l[i]>>r[i]>>t[i];
            }
            for (int i=0;i<roads.size();i++){
                istringstream s(roads[i]);
                int x,y,z;
                s>>x>>y>>z;
                tension(dist[x][y],z),tension(dist[y][x],z);
            }
            for (int k=0;k<n;k++) for (int i=0;i<n;i++) for (int j=0;j<n;j++) tension(dist[i][j],dist[i][k]+dist[k][j]);
            memset(dp,0x3f,sizeof(dp));
            for (int i=0;i<m;i++) if (dist[n-1][i]<=r[i]) tension(dp[1<<i][i],max(dist[n-1][i],l[i])+t[i]);
            for (int s=1;s<1<<m;s++) for (int i=0;i<m;i++) if (s>>i&1) for (int j=0;j<m;j++) if (~s>>j&1){ 
                if (dp[s][i]+dist[i][j]<=r[j]) tension(dp[s|1<<j][j],max(dp[s][i]+dist[i][j],l[j])+t[j]);
            }
            for (int i=1;i<1<<m;i++) popcount[i]=popcount[i>>1]+(i&1);
            int ans=0;
            for (int i=0;i<1<<m;i++) for (int j=0;j<m;j++) if (dp[i][j]!=0x3f3f3f3f) ans=max(ans,popcount[i]);
            return ans;
        }
};

// CUT begin
ifstream data("TravellingPurchasingMan.sample");

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

bool do_test(int N, vector<string> interestingStores, vector<string> roads, int __expected) {
    time_t startClock = clock();
    TravellingPurchasingMan *instance = new TravellingPurchasingMan();
    int __result = instance->maxStores(N, interestingStores, roads);
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
        vector<string> interestingStores;
        from_stream(interestingStores);
        vector<string> roads;
        from_stream(roads);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, interestingStores, roads, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476888782;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TravellingPurchasingMan (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
