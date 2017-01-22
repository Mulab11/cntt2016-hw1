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

class LeftRightDigitsGame2 {
    public:
        string dp[55][55][3][3];
        inline int calc_stat(int i,int j){
            if (i>j) return 2;
            if (i==j) return 1;
            return 0;
        }
        inline int link(int i,int j){
            if (i!=1) return i;
            return j;
        }
        inline int link(int i,int j,int k){
            return link(link(i,j),k);
        }
        string better(string a,string b){
            if (a.size()==1) return b;
            if (b.size()==1) return a;
            for (int i=0;i<(int)a.size();i++) if (a[i]!=b[i]) return a[i]<b[i]?a:b;
            return a;
        }
        string minNumber(string digits, string lowerBound) {
            int n=digits.size();
            for (int i=0;i<n;i++) for (int j=0;j<3;j++) for (int k=0;k<3;k++){
                int t=calc_stat(digits[0],lowerBound[i]);
                if (link(j,t,k)>=1) dp[i][i][j][k]=string(digits,0,1); else dp[i][i][j][k]=string("");
            }
            for (int len=1;len<n;len++) for (int l=0,r=len;r<n;l++,r++){
                for (int i=0;i<3;i++) for (int j=0;j<3;j++){
                    dp[l][r][i][j]=string("?");
                    dp[l][r][i][j]=better(dp[l][r][i][j],digits[r-l]+dp[l+1][r][link(i,calc_stat(digits[r-l],lowerBound[l]))][j]);
                    dp[l][r][i][j]=better(dp[l][r][i][j],dp[l][r-1][i][link(calc_stat(digits[r-l],lowerBound[r]),j)]+digits[r-l]);
                    if ((int)dp[l][r][i][j].size()<=r-l) dp[l][r][i][j]="";
                    //if (n<=3) printf("%d %d %d %d %d\n",l,r,i,j,int(dp[l][r][i][j].size()));
                }
            }
            return dp[0][n-1][1][1];
        }
};

// CUT begin
ifstream data("LeftRightDigitsGame2.sample");

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

bool do_test(string digits, string lowerBound, string __expected) {
    time_t startClock = clock();
    LeftRightDigitsGame2 *instance = new LeftRightDigitsGame2();
    string __result = instance->minNumber(digits, lowerBound);
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
        string digits;
        from_stream(digits);
        string lowerBound;
        from_stream(lowerBound);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(digits, lowerBound, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484325901;
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
        cout << "LeftRightDigitsGame2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
