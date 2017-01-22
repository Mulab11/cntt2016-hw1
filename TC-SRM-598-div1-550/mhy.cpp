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

class FoxAndFencing {
    public:
        string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d) {
            if (d<=mov1+rng1) return "Ciel";
            if (mov1+rng1==mov2+rng2) return "Draw";
            if (mov1+rng1>mov2+rng2){
                if (mov1>mov2&&rng1+mov1>mov2+rng2+mov2) return "Ciel";
            } else{
                if (mov1+d<=mov2+rng2) return "Liss";
                if (mov2>mov1&&rng2+mov2>mov1+rng1+mov1) return "Liss";
            }
            return "Draw";
        }
};

// CUT begin
ifstream data("FoxAndFencing.sample");

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

bool do_test(int mov1, int mov2, int rng1, int rng2, int d, string __expected) {
    time_t startClock = clock();
    FoxAndFencing *instance = new FoxAndFencing();
    string __result = instance->WhoCanWin(mov1, mov2, rng1, rng2, d);
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
        int mov1;
        from_stream(mov1);
        int mov2;
        from_stream(mov2);
        int rng1;
        from_stream(rng1);
        int rng2;
        from_stream(rng2);
        int d;
        from_stream(d);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(mov1, mov2, rng1, rng2, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1480509909;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FoxAndFencing (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
