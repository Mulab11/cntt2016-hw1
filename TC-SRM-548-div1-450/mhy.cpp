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

const double eps=1e-9;
inline int sgn(double x){return x<-eps?-1:x>eps;}

class KingdomAndDice {
    public:
        int dp[205][10005];
        double newFairness(vector<int> firstDie, vector<int> secondDie, int X) {
            int n=firstDie.size(),m=n*n,c=0,d=0;
            for (int i=0;i<n;i++) if (firstDie[i]){
                for (int j=0;j<n;j++) if (firstDie[i]>secondDie[j]) d++;
            } else c++;
            vector<int> v;
            v.push_back(-1),v.push_back(X+1);
            for (int i=0;i<n;i++) if (firstDie[i]) v.push_back(firstDie[i]);
            for (int i=0;i<n;i++) if (secondDie[i]) v.push_back(secondDie[i]);
            sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
            int q=(int)v.size()-1;
            memset(dp,0x3f,sizeof(dp));
            dp[0][0]=0;
            for (int i=1;i<=q;i++){
                int t=v[i]-v[i-1]-1,x=0;
                for (int j=0;j<n;j++) if (v[i]-1>secondDie[j]) x++;
                //printf("%d %d %d %d %d\n",i,t,x,v[i-1],v[i]);
                for (int j=0;j<=m;j++) dp[i][j]=dp[i-1][j];
                vector<int> a;a.clear();
                int now=0;
                for (int j=0;j<31;j++){
                    if (now+(1<<j)>t) break;
                    now+=1<<j;
                    a.push_back(1<<j);
                }
                if (t>now) a.push_back(t-now);
                for (int idx=a.size();idx--;){
                    long long v=1ll*a[idx]*x;
                    //printf("%d%c",a[t]," \n"[t==0]);
                    for (int j=m;j>=v;j--) dp[i][j]=min(dp[i][j],dp[i][j-v]+a[idx]);
                }
                //for (;t--;) for (int j=m;j>=x;j--) dp[i][j]=min(dp[i][j],dp[i][j-x]+1);
                //for (int j=0;j<=m;j++) for (int k=1;k<=t&&k*x<=j;k++) dp[i][j]=min(dp[i][j],dp[i-1][j-k*x]+k);
            }
            //printf("%d %d %d\n",n,c,d);
            double ans=0x3f3f3f3f,ansid=-1;
            for (int i=m;~i;i--) if (dp[q][i]<=c){
                //printf("%d\n",i);
                double tmp=1.0*(i+d)/m,t=abs(tmp-0.5);
                if (sgn(t-ans)<0||(!sgn(ans-t)&&tmp<ansid)) ans=t,ansid=tmp;
            }
            return ansid;
        }
};

// CUT begin
ifstream data("KingdomAndDice.sample");

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

bool do_test(vector<int> firstDie, vector<int> secondDie, int X, double __expected) {
    time_t startClock = clock();
    KingdomAndDice *instance = new KingdomAndDice();
    double __result = instance->newFairness(firstDie, secondDie, X);
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
        vector<int> firstDie;
        from_stream(firstDie);
        vector<int> secondDie;
        from_stream(secondDie);
        int X;
        from_stream(X);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(firstDie, secondDie, X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484325925;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "KingdomAndDice (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
