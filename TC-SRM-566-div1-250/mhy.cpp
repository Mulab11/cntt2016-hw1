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

class PenguinSledding {
    public:
        int mat[55][55];
        int d[55];
        long long countDesigns(int n, vector<int> X, vector<int> Y) {
            memset(mat,0,sizeof(mat));
            memset(d,0,sizeof(d));
            int m=X.size();
            for (int i=0;i<m;i++) X[i]--,Y[i]--,d[X[i]]++,d[Y[i]]++,mat[X[i]][Y[i]]=mat[Y[i]][X[i]]=1;
            long long ans=1;
            //for (int i=0;i<n;i++) printf("%d %d\n",i,d[i]);
            for (int i=0;i<n;i++) ans+=(1ll<<d[i])-1;
            ans-=m;
            for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) for (int k=j+1;k<n;k++) if (mat[i][j]&&mat[j][k]&&mat[k][i]) ans++;
            return ans;
        }
};

// CUT begin
ifstream data("PenguinSledding.sample");

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

bool do_test(int numCheckpoints, vector<int> checkpoint1, vector<int> checkpoint2, long long __expected) {
    time_t startClock = clock();
    PenguinSledding *instance = new PenguinSledding();
    long long __result = instance->countDesigns(numCheckpoints, checkpoint1, checkpoint2);
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
        int numCheckpoints;
        from_stream(numCheckpoints);
        vector<int> checkpoint1;
        from_stream(checkpoint1);
        vector<int> checkpoint2;
        from_stream(checkpoint2);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numCheckpoints, checkpoint1, checkpoint2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484325841;
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
        cout << "PenguinSledding (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
