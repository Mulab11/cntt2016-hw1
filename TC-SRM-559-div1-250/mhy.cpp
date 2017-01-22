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

class HyperKnight {
    public:
        long long countCells(int a, int b, int n, int m, int k) {
            vector<int> A,B;
            A.push_back(0);
            A.push_back(a);
            A.push_back(b);
            A.push_back(n-a);
            A.push_back(n-b);
            A.push_back(n);
            sort(A.begin(),A.end());
            B.push_back(0);
            B.push_back(a);
            B.push_back(b);
            B.push_back(m-a);
            B.push_back(m-b);
            B.push_back(m);
            sort(B.begin(),B.end());
            long long ans=0;
            for (int i=0;i+1<(int)A.size();i++) for (int j=0;j+1<(int)B.size();j++){
                int c=0,x=A[i],y=B[j];
                if (x-a>=0&&y-b>=0) c++;
                if (x-a>=0&&y+b<m) c++;
                if (x+a<n&&y-b>=0) c++;
                if (x+a<n&&y+b<m) c++;
                if (x-b>=0&&y-a>=0) c++;
                if (x-b>=0&&y+a<m) c++;
                if (x+b<n&&y-a>=0) c++;
                if (x+b<n&&y+a<m) c++;
                if (c==k) ans+=1ll*(A[i+1]-A[i])*(B[j+1]-B[j]);
            }
            return ans;
        }
};

// CUT begin
ifstream data("HyperKnight.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int a, int b, int numRows, int numColumns, int k, long long __expected) {
    time_t startClock = clock();
    HyperKnight *instance = new HyperKnight();
    long long __result = instance->countCells(a, b, numRows, numColumns, k);
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
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int numRows;
        from_stream(numRows);
        int numColumns;
        from_stream(numColumns);
        int k;
        from_stream(k);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, numRows, numColumns, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483630362;
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
        cout << "HyperKnight (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
