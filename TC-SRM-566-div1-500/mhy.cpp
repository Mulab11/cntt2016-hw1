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

class PenguinEmperor {
    public:
        static const int mod=1000000007;
        int mat[405][405];
        int dp[405];
        void trans(int n,int *a,int *b,int *c){
            static int t[405];
            memset(t,0,sizeof(t));
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) (t[(i+j)%n]+=1ll*a[i]*b[j]%mod)%=mod;
            memcpy(c,t,sizeof(t));
        }
        int countJourneys(int n, long long m) {
            memset(mat,0,sizeof(mat));
            mat[0][0]=1;
            for (int i=1;i<n;i++) for (int j=0;j<n;j++){
                if (i+i!=n) mat[i][j]=(mat[i-1][(j+i)%n]+mat[i-1][(j+n-i)%n])%mod;
                else mat[i][j]=mat[i-1][(j+i)%n];
            }
            dp[0]=1;
            trans(n,dp,mat[m%n],dp);
            m/=n;
            for (;m;m>>=1,trans(n,mat[n-1],mat[n-1],mat[n-1])) if (m&1) trans(n,dp,mat[n-1],dp);
            return dp[0];
        }
};

// CUT begin
ifstream data("PenguinEmperor.sample");

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

bool do_test(int numCities, long long daysPassed, int __expected) {
    time_t startClock = clock();
    PenguinEmperor *instance = new PenguinEmperor();
    int __result = instance->countJourneys(numCities, daysPassed);
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
        int numCities;
        from_stream(numCities);
        long long daysPassed;
        from_stream(daysPassed);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(numCities, daysPassed, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484325845;
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
        cout << "PenguinEmperor (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
