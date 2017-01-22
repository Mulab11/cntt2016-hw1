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

class EllysRoomAssignmentsDiv1 {
    public:
        vector<pair<int,int> > a;
        double getAverage(vector<string> ratings) {
            string ss;
            for (int i=0;i<(int)ratings.size();i++) ss+=ratings[i];
            stringstream strin(ss);
            int n=0,m=0;
            a.clear();
            for (int x;strin>>x;) a.push_back(make_pair(x,n)),n++;
            int c=(n+19)/20;
            //printf("%d %d\n",n,c);
            sort(a.rbegin(),a.rend());
            int i;
            double ans=0;
            for (i=0;i+c<=n;i+=c,m++){
                int tag=0;
                double sum=0;
                for (int j=0;j<c;j++) if (!a[i+j].second) tag=1,ans+=a[i+j].first; else sum+=a[i+j].first;
                if (tag) continue;
                ans+=sum/c;
            }
            if (i<n){
                //printf("%d %d %d %d\n",n,m,c,n-i);
                double sum=0;
                int tag=0;
                for (int j=i;j<n;j++) if (!a[j].second) tag=1,ans+=a[j].first; else sum+=a[j].first;
                if (tag) return ans/(m+1);
                double poss=1.0*(n-i)/c;
                //printf("%.3f\n",poss);
                return poss*(ans+sum/(n-i))/(m+1)+(1-poss)*ans/m;
            } else{
                return ans/m;
            }
        }
};

// CUT begin
ifstream data("EllysRoomAssignmentsDiv1.sample");

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

bool do_test(vector<string> ratings, double __expected) {
    time_t startClock = clock();
    EllysRoomAssignmentsDiv1 *instance = new EllysRoomAssignmentsDiv1();
    double __result = instance->getAverage(ratings);
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
        vector<string> ratings;
        from_stream(ratings);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(ratings, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483456592;
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
        cout << "EllysRoomAssignmentsDiv1 (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
