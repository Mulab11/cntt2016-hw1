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

class AlternateColors2 {
    public:
        long long countWays(int n, int k) {
            long long ans=0;
            for (int i=0;i*3<=n;i++){
                if (k<=3*i){
                    if (k%3!=1) continue;
                    if (i*3==n){ans++;continue;}
                    ans+=3*(n-3*i);
                } else{
                    int m=n-3*i;
                    ans++;
                    /*
                    k-3*i<=2*min(j,m-j)
                    (k-3*i+1)/2<=m-j
                    j<=m-(k-3*i+1)/2
                    */
                    if (~m&1){
                        if ((k-3*i)%2==1) ans+=2;
                    }
                    if ((k-3*i)%2==1){
                        int l=max((k-3*i+1)>>1,0),r=(m-1)>>1;
                        if (l<=r) ans+=2*(r-l+1);
                    }
                    if ((k-3*i)%2==1){
                        int l=(m>>1)+1,r=min(m-((k-3*i+1)>>1),m-1);
                        if (l<=r) ans+=2*(r-l+1);
                    }
                    if (1){
                        int l=max((m>>1)+1,m-((k-3*i+1)>>1)+1),r=m-1;
                        if (l<=r) ans+=2*(r-l+1);
                    }
                    /*
                    for (int f=0;f<2;f++)
                    for (int j=0;j<m;j++){
                        int mid=2*min(j,m-j);
                        if (k-3*i<=mid){
                            if ((k-3*i)%2==1) ans++;
                        } else{
                            if (j*2>m) ans++;
                        }
                    }
                    */
                }
            }
            return ans;
        }
};

// CUT begin
ifstream data("AlternateColors2.sample");

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

bool do_test(int n, int k, long long __expected) {
    time_t startClock = clock();
    AlternateColors2 *instance = new AlternateColors2();
    long long __result = instance->countWays(n, k);
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
        int n;
        from_stream(n);
        int k;
        from_stream(k);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483287642;
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
        cout << "AlternateColors2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
