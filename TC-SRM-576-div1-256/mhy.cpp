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

class ArcadeManao {
    public:
        int n,m;
        int inq[55*55];
        int queue[55*55],q;
        inline int id(int i,int j){if (i<0||i>=n||j<0||j>=m) return 0;return i*m+j+1;}
        int shortestLadder(vector<string> level, int coinRow, int coinColumn) {
            memset(inq,0,sizeof(inq));
            n=level.size(),m=level[0].size();
            inq[0]=1;
            inq[queue[q=1]=id(n-1,m-1)]=1;
            for (int len=0;;len++){
                //printf("%d\n",len);
                for (int l=1,&r=q;l<=r;l++){
                    int x=(queue[l]-1)/m,y=(queue[l]-1)%m;
                    if (level[x][y]=='.') continue;
                    //printf("%d %d\n",x,y);
                    for (int k=1;k<=len;k++) if (!inq[id(x+k,y)]) inq[queue[++r]=id(x+k,y)]=1;
                    for (int k=1;k<=len;k++) if (!inq[id(x-k,y)]) inq[queue[++r]=id(x-k,y)]=1;
                    if (!inq[id(x,y-1)]) inq[queue[++r]=id(x,y-1)]=1;
                    if (!inq[id(x,y+1)]) inq[queue[++r]=id(x,y+1)]=1;
                }
                if (inq[id(coinRow-1,coinColumn-1)]) return len;
            }
            return -1;
        }
};

// CUT begin
ifstream data("ArcadeManao.sample");

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

bool do_test(vector<string> level, int coinRow, int coinColumn, int __expected) {
    time_t startClock = clock();
    ArcadeManao *instance = new ArcadeManao();
    int __result = instance->shortestLadder(level, coinRow, coinColumn);
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
        vector<string> level;
        from_stream(level);
        int coinRow;
        from_stream(coinRow);
        int coinColumn;
        from_stream(coinColumn);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(level, coinRow, coinColumn, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1476888830;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 256 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ArcadeManao (256 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
