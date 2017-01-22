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

class PolygonTraversal {
    public:
        long long dp[1<<18][18];
        long long count(int n, vector<int> points) {
            memset(dp,0,sizeof(dp));
            int m=points.size(),s0=0;
            for (int i=0;i<m;i++) s0|=1<<(--points[i]);
            dp[s0][points[m-1]]=1;
            for (int s=0;s<1<<n;s++) for (int i=0;i<n;i++) if (s>>i&1) if (dp[s][i]){
                for (int j=0;j<n;j++) if (~s>>j&1){
                    int tag=0;
                    for (int k=i+1;(k=(k+n)%n)!=j;k++) if (s>>k&1) tag=1;
                    if (!tag) continue;
                    tag=0;
                    for (int k=i-1;(k=(k+n)%n)!=j;k--) if (s>>k&1) tag=1;
                    if (!tag) continue;
                    //printf("%d %d %d\n",s,i,j);
                    dp[s|1<<j][j]+=dp[s][i];
                }
            }
            long long ans=0;
            for (int i=0;i<n;i++) if (points[0]!=i&&(points[0]+1+n)%n!=i&&(points[0]-1+n)%n!=i) ans+=dp[(1<<n)-1][i];
            return ans;
        }
};

// CUT begin
ifstream data("PolygonTraversal.sample");

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

bool do_test(int N, vector<int> points, long long __expected) {
    time_t startClock = clock();
    PolygonTraversal *instance = new PolygonTraversal();
    long long __result = instance->count(N, points);
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
        vector<int> points;
        from_stream(points);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, points, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483456442;
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
        cout << "PolygonTraversal (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
