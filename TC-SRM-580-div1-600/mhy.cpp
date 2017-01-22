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

class ShoutterDiv1 {
    public:
        string trans(vector<string> a){
            string ans;
            for (int i=0;i<(int)a.size();i++) ans+=a[i];
            return ans;
        }
        vector<int> trans(vector<string> a1000,vector<string> a100,vector<string> a10,vector<string> a1){
            string b1000=trans(a1000),b100=trans(a100),b10=trans(a10),b1=trans(a1);
            vector<int> ans;
            for (int i=0;i<(int)b1.size();i++) ans.push_back(b1000[i]*1000+b100[i]*100+b10[i]*10+b1[i]);
            return ans;
        }
        int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1) {
            vector<int> a=trans(s1000,s100,s10,s1),b=trans(t1000,t100,t10,t1);
            int n=a.size();
            for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (a[i]!=a[j]?a[i]>a[j]:b[i]<b[j]) swap(a[i],a[j]),swap(b[i],b[j]);
            int minb=b[0];for (int i=1;i<n;i++) minb=min(minb,b[i]);
            int ans=0;
            for (int i=0;i<n;i++){
                int now=minb;
                for (int j=0;j<n;ans++){
                    if (a[i]<=now) now=max(now,b[i]);
                    int maxb=-1;
                    for (;j<n&&a[j]<=now;j++) maxb=max(maxb,b[j]);
                    if (j==n) break;
                    if (maxb<0) return -1;
                    now=maxb;
                }
            }
            return ans;
        }
};

// CUT begin
ifstream data("ShoutterDiv1.sample");

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

bool do_test(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1, int __expected) {
    time_t startClock = clock();
    ShoutterDiv1 *instance = new ShoutterDiv1();
    int __result = instance->count(s1000, s100, s10, s1, t1000, t100, t10, t1);
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
        vector<string> s1000;
        from_stream(s1000);
        vector<string> s100;
        from_stream(s100);
        vector<string> s10;
        from_stream(s10);
        vector<string> s1;
        from_stream(s1);
        vector<string> t1000;
        from_stream(t1000);
        vector<string> t100;
        from_stream(t100);
        vector<string> t10;
        from_stream(t10);
        vector<string> t1;
        from_stream(t1);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s1000, s100, s10, s1, t1000, t100, t10, t1, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475717641;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ShoutterDiv1 (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
