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

class BoundedOptimization {
    public:
        int map[20][20];
        double a[20];
        double maxValue(vector<string> expr, vector<int> lowerBound, vector<int> upperBound, int maxSum) {
            memset(map,0,sizeof(map));
            string sumstr;
            for (int i=0;i<(int)expr.size();i++) sumstr+=expr[i];
            for (int i=0;i<(int)sumstr.size();i++) if (!i||sumstr[i-1]=='+'){
                int x=sumstr[i]-'a',y=sumstr[i+1]-'a';
                map[x][y]=map[y][x]=1;
            }
            int n=lowerBound.size();
            double ans=0;
            for (int s0=0;s0<1<<n;s0++){
                bool isclique=true;
                for (int i=0;i<n;i++) if (~s0>>i&1) for (int j=i+1;j<n;j++) if (~s0>>j&1) if (!map[i][j]) isclique=false;
                if (!isclique) continue;
                for (int s=s0;;s=s0&(s-1)){
                    memset(a,0,sizeof(a));
                    double sum=maxSum,c=0,nowans=0;
                    int k=0;
                    for (int i=0;i<n;i++) if (s0>>i&1){
                        if (s>>i&1) a[i]=lowerBound[i]; else a[i]=upperBound[i];
                        sum-=a[i];
                    }
                    if (sum<0) goto end;
                    for (int i=0;i<n;i++) if (~s0>>i&1) for (int j=0;j<n;j++) if (s0>>j&1) if (map[i][j]) a[i]+=a[j];
                    for (int i=0;i<n;i++) if (~s0>>i&1) k++;
                    for (int i=0;i<n;i++) if (~s0>>i&1) c+=a[i]+sum/2;
                    c=k?(c-sum)/k:666;
                    for (int i=0;i<n;i++) if (~s0>>i&1) a[i]=a[i]+sum/2-c;
                    for (int i=0;i<n;i++) if (a[i]<lowerBound[i]||upperBound[i]<a[i]) goto end;
                    for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (map[i][j]) nowans+=1.*a[i]*a[j];
                    ans=max(ans,nowans);
                    end:;
                    if (!s) break;
                }
            }
            return ans;
        }
};

// CUT begin
ifstream data("BoundedOptimization.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> expr, vector<int> lowerBound, vector<int> upperBound, int maxSum, double __expected) {
    time_t startClock = clock();
    BoundedOptimization *instance = new BoundedOptimization();
    double __result = instance->maxValue(expr, lowerBound, upperBound, maxSum);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<string> expr;
        from_stream(expr);
        vector<int> lowerBound;
        from_stream(lowerBound);
        vector<int> upperBound;
        from_stream(upperBound);
        int maxSum;
        from_stream(maxSum);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(expr, lowerBound, upperBound, maxSum, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475649277;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BoundedOptimization (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
