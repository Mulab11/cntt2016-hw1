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

class DrawingPointsDivOne {
    public:
        int vis[505][505],s[505][505];
        inline int calc(int x1,int y1,int x2,int y2){return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];}
        int maxSteps(vector<int> x, vector<int> y) {
            int n=x.size();
            for (int i=0;i<n;i++) x[i]+=100,y[i]+=100,vis[x[i]][y[i]]=1;
            int l=0,r=200;
            for (int ok,mid;r-l>1;(ok?l:r)=mid){
                mid=(l+r)>>1;
                memset(s,0,sizeof(s));
                for (int i=0;i<n;i++) for (int j=0;j<=mid;j++) for (int k=0;k<=mid;k++) s[x[i]+j][y[i]+k]=1;
                for (int i=1;i<=500;i++) for (int j=1;j<=500;j++) s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
                ok=true;
                for (int i=mid;i<=500;i++) for (int j=mid;j<=500;j++) if (calc(i-mid,j-mid,i,j)==(mid+1)*(mid+1)&&!vis[i-mid][j-mid]){
                    ok=false;
                }
            }
            return r!=200?l:-1;
        }
};

// CUT begin
ifstream data("DrawingPointsDivOne.sample");

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

bool do_test(vector<int> x, vector<int> y, int __expected) {
    time_t startClock = clock();
    DrawingPointsDivOne *instance = new DrawingPointsDivOne();
    int __result = instance->maxSteps(x, y);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475649273;
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
        cout << "DrawingPointsDivOne (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
