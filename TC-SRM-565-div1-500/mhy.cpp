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

class TheDivisionGame {
    public:
        int a[1000005];
        int sg[1000005],c[1000005];
        long long countWinningIntervals(int L, int R) {
            for (int i=L;i<=R;i++) a[i-L]=i;
            for (int i=2;i*i<=R;i++)
                for (int j=(L+i-1)/i*i;j<=R;j+=i)
                    for (;a[j-L]%i==0;a[j-L]/=i) sg[j-L]++;
            for (int i=L;i<=R;i++) if (a[i-L]>1) sg[i-L]++;
            //for (int i=L;i<=R;i++) printf("%d %d\n",i,sg[i-L]);
            long long ans=(R-L+2ll)*(R-L+1ll)>>1;
            memset(c,0,sizeof(c));
            c[0]++;
            for (int i=0,t=0;i<=R-L;i++) t^=sg[i],ans-=c[t]++;
            return ans;
        }
};

// CUT begin
ifstream data("TheDivisionGame.sample");

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

bool do_test(int L, int R, long long __expected) {
    time_t startClock = clock();
    TheDivisionGame *instance = new TheDivisionGame();
    long long __result = instance->countWinningIntervals(L, R);
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
        int L;
        from_stream(L);
        int R;
        from_stream(R);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(L, R, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483803587;
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
        cout << "TheDivisionGame (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
