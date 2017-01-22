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

const int mod=555555555;

class XorBoard {
    public:
        int C[3005][3005];
        int count(int n, int m, int Rcount, int Ccount, int S) {
            for (int i=0;i<=3000;*C[i++]=1) for (int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
            int ans=0;
            for (int i=0;i<=n&&i<=Rcount;i++) for (int j=0;j<=m&&j<=Ccount;j++) if (i*m+j*n-i*j*2==S){
                if ((Rcount-i)&1) continue;
                if ((Ccount-j)&1) continue;
                int x=(Rcount-i)>>1,y=(Ccount-j)>>1;
                ans=(ans+1ll*C[n][i]*C[m][j]%mod*C[n+x-1][n-1]%mod*C[m+y-1][m-1])%mod;
                //if (n==2&&m==2) printf("%d %d %d %d %d %d\n",i,j,x,y,ans,i*m+j*n-i*j*2);
            }
            return ans;
        }
};

// CUT begin
ifstream data("XorBoard.sample");

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

bool do_test(int H, int W, int Rcount, int Ccount, int S, int __expected) {
    time_t startClock = clock();
    XorBoard *instance = new XorBoard();
    int __result = instance->count(H, W, Rcount, Ccount, S);
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
        int H;
        from_stream(H);
        int W;
        from_stream(W);
        int Rcount;
        from_stream(Rcount);
        int Ccount;
        from_stream(Ccount);
        int S;
        from_stream(S);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(H, W, Rcount, Ccount, S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484325809;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 555 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "XorBoard (555 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
