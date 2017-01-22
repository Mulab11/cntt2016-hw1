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

template <typename T> inline void tension(T &a,const T &b){if (a>b) a=b;}

class Stamp {
    public:
        int dp[55][3];
        int getMinimumCost(string desiredColor, int stampCost, int pushCost) {
            int n=desiredColor.size(),ans=0x3f3f3f3f;
            for (int l=1;l<=n;l++){
                memset(dp,0x3f,sizeof(dp));
                dp[0][0]=dp[0][1]=dp[0][2]=stampCost*l;
                for (int i=l;i<=n;i++){
                    for (int f=0;f<3;f++){
                        int ok=1;
                        for (int j=i-l+1;j<=i;j++) if (desiredColor[j-1]!='*'&&desiredColor[j-1]!="RGB"[f]) {ok=0;break;}
                        if (!ok) continue;
                        for (int j=0;j<3;j++) tension(dp[i][f],dp[i-l][j]+pushCost);
                        for (int j=i-l+1;j<i;j++) tension(dp[i][f],dp[j][f]+pushCost);
                    }
                }
                tension(ans,min(dp[n][0],min(dp[n][1],dp[n][2])));
            }
            return ans;
        }
};

// CUT begin
ifstream data("Stamp.sample");

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

bool do_test(string desiredColor, int stampCost, int pushCost, int __expected) {
    time_t startClock = clock();
    Stamp *instance = new Stamp();
    int __result = instance->getMinimumCost(desiredColor, stampCost, pushCost);
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
        string desiredColor;
        from_stream(desiredColor);
        int stampCost;
        from_stream(stampCost);
        int pushCost;
        from_stream(pushCost);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(desiredColor, stampCost, pushCost, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475213999;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 275 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Stamp (275 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
