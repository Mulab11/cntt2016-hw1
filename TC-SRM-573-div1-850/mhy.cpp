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

const int mod=1000000007;
inline long long inverse(long long x){
    long long ans=1;
    for (int y=mod-2;y;y>>=1,x=x*x%mod) if (y&1) ans=ans*x%mod;
    return ans;
}

class WolfPack {
    public:
        long long fact[1000005],ifact[1000005];
        inline long long C(int n,int m){return n>m?fact[n]*ifact[n-m]%mod*ifact[m]%mod:n==m;}
        void init(int n=1000000){
            *fact=1;for (int i=1;i<=n;i++) fact[i]=fact[i-1]*i%mod;
            ifact[n]=inverse(fact[n]);for (int i=n;i;i--) ifact[i-1]=ifact[i]*i%mod;
        }
        struct rec{int x,y;} a[105];
        int calc(vector<int> X, vector<int> Y, int m) {
            init();
            int n=X.size();
            for (int i=0;i<n;i++) a[i].x=X[i]+Y[i],a[i].y=X[i]-Y[i];
            long long ans1=0;
            for (int i=-400000;i<=400000;i++){
                long long sum=1;
                for (int _j=0;_j<n;_j++){
                    int j=a[_j].x;
                    if ((i+m-j)&1) sum=0;
                    if ((m-i+j)&1) sum=0;
                    int x=(i+m-j)>>1,y=(m-i+j)>>1;
                    if (x<0||y<0) sum=0;
                    sum=sum*C(m,x)%mod;
                }
                ans1+=sum;
            }
            ans1%=mod;
            long long ans2=0;
            for (int i=-400000;i<=400000;i++){
                long long sum=1;
                for (int _j=0;_j<n;_j++){
                    int j=a[_j].y;
                    if ((i+m-j)&1) sum=0;
                    if ((m-i+j)&1) sum=0;
                    int x=(i+m-j)>>1,y=(m-i+j)>>1;
                    if (x<0||y<0) sum=0;
                    sum=sum*C(m,x)%mod;
                }
                ans2+=sum;
            }
            ans2%=mod;
            //printf("%lld %lld\n",ans1,ans2);
            return ans1*ans2%mod;
        }
};

// CUT begin
ifstream data("WolfPack.sample");

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

bool do_test(vector<int> x, vector<int> y, int m, int __expected) {
    time_t startClock = clock();
    WolfPack *instance = new WolfPack();
    int __result = instance->calc(x, y, m);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        int m;
        from_stream(m);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, m, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475846944;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 850 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "WolfPack (850 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
