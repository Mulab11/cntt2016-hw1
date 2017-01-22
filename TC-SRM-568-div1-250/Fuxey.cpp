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

class BallsSeparating {
    int INF = 0x3f3f3f3f;
    public:
    bool hasOne(vector<int> a)
    {
        for(int i=0;i<a.size();i++) if(a[i]) return true;
        return false;
    }
    
    int d[100][10];
    int minOperations(vector<int> red, vector<int> green, vector<int> blue) {
        int Set = hasOne(red) + hasOne(green)*2 + hasOne(blue) * 4;
        if(__builtin_popcount(Set) > red.size()) return -1;
        
        for(int i=0;i<=red.size();i++) for(int j=0;j<=Set;j++) d[i][j] = INF;
        d[0][0] = 0;
        
        for(int i=0;i<red.size();i++) for(int j=0;j<=Set;j++)
        {
            d[i+1][j] = red[i] + green[i] + blue[i] - max(red[i], max(green[i], blue[i])) + d[i][j];
            if(j | 1) d[i+1][j] = min(d[i+1][j], d[i][j^1] + green[i] + blue[i]);
            if(j | 2) d[i+1][j] = min(d[i+1][j], d[i][j^2] + red[i] + blue[i]);
            if(j | 4) d[i+1][j] = min(d[i+1][j], d[i][j^4] + red[i] + green[i]);
        }
        return d[red.size()][Set];
    }
};
// CUT begin
ifstream data("BallsSeparating.sample");

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

bool do_test(vector<int> red, vector<int> green, vector<int> blue, int __expected) {
    time_t startClock = clock();
    BallsSeparating *instance = new BallsSeparating();
    int __result = instance->minOperations(red, green, blue);
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
        vector<int> red;
        from_stream(red);
        vector<int> green;
        from_stream(green);
        vector<int> blue;
        from_stream(blue);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(red, green, blue, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1479028474;
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
        cout << "BallsSeparating (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
