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

class Constellation {
    public:
        inline bool ok(int i,int j,int k){
            if (i<=k&&k<=j) return true;
            if (j<=k&&k<=i) return true;
            return false;
        }
        double expectation(vector<int> x, vector<int> y, vector<int> prob) {
            int n=x.size();
            double ans=0;
            for (int i=0;i<n;i++) for (int j=0;j<n;j++){
                double s=1ll*(x[i])*(y[j]-y[i])-1ll*(x[j]-x[i])*(y[i]);
                s*=prob[i]/1000.0*prob[j]/1000.0;
                for (int k=0;k<n;k++) if (i!=k&&j!=k){
                    long long t=1ll*(x[j]-x[i])*(y[k]-y[i])-1ll*(x[k]-x[i])*(y[j]-y[i]);
                    if (t<0) s*=(1-prob[k]/1000.0);
                    if (t==0){
                        if (ok(x[i],x[j],x[k])&&ok(y[i],y[j],y[k])) s*=(1-prob[k]/1000.0);
                    }
                }
                //printf("%d %d %.6f\n",i,j,s);
                ans+=s;
            }
            return ans/2;
        }
};

// CUT begin
ifstream data("Constellation.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> x, vector<int> y, vector<int> prob, double __expected) {
    time_t startClock = clock();
    Constellation *instance = new Constellation();
    double __result = instance->expectation(x, y, prob);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        vector<int> prob;
        from_stream(prob);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, prob, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483803672;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Constellation (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
