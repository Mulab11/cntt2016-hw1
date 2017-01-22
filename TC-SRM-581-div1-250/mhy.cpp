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

class SurveillanceSystem {
    public:
        int a[105],c[105];
        int ok1[105],ok2[105];
        string getContainerInfo(string containers, vector<int> reports, int L) {
            memset(a,0,sizeof(a));
            int n=containers.size(),m=reports.size();
            for (int i=0;i+L<=n;i++) for (int j=0;j<L;j++) a[i]+=containers[i+j]=='X';
            memset(ok1,0,sizeof(ok1)),memset(ok2,0,sizeof(ok2));
            for (int i=0;i<=n;i++){
                memset(c,0,sizeof(c));
                int c1=0,c2=0;
                for (int j=0;j+L<=n;j++) if (a[j]==i){
                    c1++;
                    for (int k=0;k<L;k++) c[j+k]++;
                }
                for (int j=0;j<m;j++) if (reports[j]==i) c2++;
                for (int j=0;j<n;j++) if (c1-c[j]<c2) ok2[j]=1;
                for (int j=0;j<n;j++) if (c[j]>0&&c2) ok1[j]=1;
                /*
                string ans;
                for (int j=0;j<n;j++) ans=ans+(ok2[j]?"+":ok1[j]?"?":"-");
                puts(ans.c_str());
                */
            }
            string ans;
            for (int j=0;j<n;j++) ans=ans+(ok2[j]?"+":ok1[j]?"?":"-");
            return ans;
        }
};

// CUT begin
ifstream data("SurveillanceSystem.sample");

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

bool do_test(string containers, vector<int> reports, int L, string __expected) {
    time_t startClock = clock();
    SurveillanceSystem *instance = new SurveillanceSystem();
    string __result = instance->getContainerInfo(containers, reports, L);
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
        string containers;
        from_stream(containers);
        vector<int> reports;
        from_stream(reports);
        int L;
        from_stream(L);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(containers, reports, L, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483456555;
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
        cout << "SurveillanceSystem (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
