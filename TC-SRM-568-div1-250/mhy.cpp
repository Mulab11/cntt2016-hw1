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
template <typename T> inline void tension(T &a, const T &b){if (a>b) a=b;}
class BallsSeparating {
    public:
    int minOperations(vector<int> red, vector<int> green, vector<int> blue) {
        //这里是算法一
        int n=red.size();
        if (n<3) return -1;
        int ans=0x3f3f3f3f;
        for (int i=0;i<n;i++) for (int j=0;j<n;j++) for (int k=0;k<n;k++) if (i!=j&&j!=k&&k!=i){
            int sum=0;
            for (int l=0;l<n;l++) if (l==i){//特判
                sum+=green[l]+blue[l];
            } else if (l==j){
                sum+=red[l]+blue[l];
            } else if (l==k){
                sum+=red[l]+green[l];
            } else{
                //选最小的
                if (red[l]>=green[l]&&red[l]>=blue[l]) sum+=green[l]+blue[l];
                else if (green[l]>=red[l]&&green[l]>=blue[l]) sum+=red[l]+blue[l];
                else sum+=red[l]+green[l];
            }
            tension(ans,sum);
        }
        return ans;
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
        int T = time(NULL) - 1475161690;
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
