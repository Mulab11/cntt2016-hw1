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
#include <numeric>

using namespace std;

template <typename T> inline void tension(T &a,const T &b){if (a>b) a=b;}

class ICPCBalloons {
    public:
        int solve(vector<int> a,vector<int> b){
            sort(a.rbegin(),a.rend()),sort(b.rbegin(),b.rend());
            int ans=accumulate(b.begin(),b.end(),0);
            if (ans>accumulate(a.begin(),a.end(),0)) return 0x3f3f3f3f;
            for (int i=0;i<(int)a.size()&&i<(int)b.size();i++) ans-=min(a[i],b[i]);
            return ans;
        }
        int minRepaintings(vector<int> balloonCount, string balloonSize, vector<int> maxAccepted) {
            int n=balloonCount.size(),m=maxAccepted.size();
            vector<int> a,b;
            for (int i=0;i<n;i++) (balloonSize[i]=='M'?a:b).push_back(balloonCount[i]);
            int ans=0x3f3f3f3f;
            for (int s=0;s<1<<m;s++){
                vector<int> c,d;
                for (int i=0;i<m;i++) (s>>i&1?c:d).push_back(maxAccepted[i]);
                tension(ans,solve(a,c)+solve(b,d));
            }
            return ans!=0x3f3f3f3f?ans:-1;
        }
};

// CUT begin
ifstream data("ICPCBalloons.sample");

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

bool do_test(vector<int> balloonCount, string balloonSize, vector<int> maxAccepted, int __expected) {
    time_t startClock = clock();
    ICPCBalloons *instance = new ICPCBalloons();
    int __result = instance->minRepaintings(balloonCount, balloonSize, maxAccepted);
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
        vector<int> balloonCount;
        from_stream(balloonCount);
        string balloonSize;
        from_stream(balloonSize);
        vector<int> maxAccepted;
        from_stream(maxAccepted);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(balloonCount, balloonSize, maxAccepted, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475294412;
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
        cout << "ICPCBalloons (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
