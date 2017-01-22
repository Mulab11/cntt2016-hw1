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

const int mod=1000000009;
inline long long inverse(long long x){
    long long ans=1;
    for (int y=mod-2;y;y>>=1,x=x*x%mod) if (y&1) ans=ans*x%mod;
    return ans;
}

int _mod;
class MegaFactorial {
    public:
        struct Matrix{
            int a[20][20];
            static const int n=20;
            void init0(){for (int i=0;i<n;i++) for (int j=0;j<n;j++) a[i][j]=0;}
            void init1(){for (int i=0;i<n;i++) for (int j=0;j<n;j++) a[i][j]=i==j;}
            friend inline Matrix operator *(const Matrix &a,const Matrix &b){
                static Matrix c;c.init0();
                for (int i=0;i<n;i++) for (int j=0;j<n;j++) for (int k=0;k<n;k++) c.a[i][k]=(c.a[i][k]+(long long)a.a[i][j]*b.a[j][k])%_mod;
                return c;
            }
        };
        inline Matrix qpow(Matrix x,int y,int mod){
            _mod=mod;
            static Matrix ans;ans.init1();
            for (;y;y>>=1,x=x*x) if (y&1) ans=ans*x;
            return ans;
        }
        int calc(int N,int n,int p,int mod){
            _mod=mod;
            static Matrix x,ans;x.init0(),ans.init1();
            for (int i=1;i<=n;i++) for (int j=1;j<=i;j++) x.a[i][j]=1;x.a[0][0]=1;
            for (;N;N/=p){
                ans=ans*qpow(x,N%p,mod);
                x=qpow(x,p,mod);
                for (int i=1;i<=n;i++) (x.a[i][0]+=1)%=mod;
            }
            int sum=ans.a[n][0];
            return sum;
        }
        int countTrailingZeros(int N, int K, int B){
            if (B==2||B==3||B==5||B==7) return calc(N,K,B,mod);
            if (B==6) return calc(N,K,3,mod);
            if (B==10) return calc(N,K,5,mod);
            if (B==4) return (calc(N,K,2,mod)+mod-calc(N,K,2,2))%mod*inverse(2)%mod;
            if (B==8) return (calc(N,K,2,mod)+mod-calc(N,K,2,3))%mod*inverse(3)%mod;
            if (B==9) return (calc(N,K,3,mod)+mod-calc(N,K,3,2))%mod*inverse(2)%mod;
            return -1;
        }
};

// CUT begin
ifstream data("MegaFactorial.sample");

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

bool do_test(int N, int K, int B, int __expected) {
    time_t startClock = clock();
    MegaFactorial *instance = new MegaFactorial();
    int __result = instance->countTrailingZeros(N, K, B);
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
        int N;
        from_stream(N);
        int K;
        from_stream(K);
        int B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483150812;
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
        cout << "MegaFactorial (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
