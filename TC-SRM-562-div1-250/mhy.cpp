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

class PastingPaintingDivOne {
    public:
        int mat[1005][1005];
        vector<long long> countColors(vector<string> clipboard, int T) {
            memset(mat,0,sizeof(mat));
            int n=clipboard.size(),m=clipboard[0].size();
            vector<long long> ans;
            ans.push_back(0ll),ans.push_back(0ll),ans.push_back(0ll);
            for (int t=0;t<T;t++){
                long long cnt[]={0ll,0ll,0ll};
                for (int i=0;i<n;i++) for (int j=0;j<m;j++){
                    int c=clipboard[i][j];
                    if (c=='.') continue;
                    if (mat[i+t][j+t]) cnt[mat[i+t][j+t]-1]--;
                    if (c=='R'){
                        mat[i+t][j+t]=1;
                    } else if (c=='G'){
                        mat[i+t][j+t]=2;
                    } else if (c=='B'){
                        mat[i+t][j+t]=3;
                    }
                    cnt[mat[i+t][j+t]-1]++;
                }
                if (t>=100){
                    for (int i=0;i<3;i++) ans[i]+=(T-t)*cnt[i];
                    break;
                }
                ans[0]+=cnt[0],ans[1]+=cnt[1],ans[2]+=cnt[2];
            }
            return ans;
        }
};

// CUT begin
ifstream data("PastingPaintingDivOne.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<string> clipboard, int T, vector<long long> __expected) {
    time_t startClock = clock();
    PastingPaintingDivOne *instance = new PastingPaintingDivOne();
    vector<long long> __result = instance->countColors(clipboard, T);
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
        vector<string> clipboard;
        from_stream(clipboard);
        int T;
        from_stream(T);
        next_line();
        vector<long long> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(clipboard, T, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483287667;
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
        cout << "PastingPaintingDivOne (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
