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
inline long long qpow(long long x,int y){
    long long ans=1;
    for (;y;y>>=1,x=x*x%mod) if (y&1) ans=ans*x%mod;
    return ans;
}

class LittleElephantAndBoard {
    public:
        static const int MAXN=2000005;
        long long fact[MAXN],ifact[MAXN];
        void init(int n=2000000){
            *fact=1;for (int i=1;i<=n;i++) fact[i]=fact[i-1]*i%mod;
            ifact[n]=inverse(fact[n]);for (int i=n;i;i--) ifact[i-1]=ifact[i]*i%mod;
        }
        inline long long C(int n,int m){return n>m?fact[n]*ifact[n-m]%mod*ifact[m]%mod:n==m;}
        long long calc(int R,int G,int B){
            if (R<0||G<0||B<0) return 0;
            long long ans=0;
            for (int i=0;i<=R+1;i++){
                if (i<0||i>R+1||i>G) continue;
                int j=i-(G-B);
                if (j<0||j>R+1||j>B) continue;
                if (i+j>R+1) continue;
                ans=(ans+qpow(2,R+1-i-j)*C(R+1,i)%mod*C(R+1-i,j)%mod*C(G-i+i+j-1,R+1-1))%mod;
            }
            return ans;
        }
        int getNumber(int n, int R, int G, int B) {
            init();
            R=n-R,G=n-G,B=n-B;
            return (calc(R-2,G,B)+2*calc(R-1,G,B)+calc(R,G,B))%mod*2%mod;
        }
};

// CUT begin
ifstream data("LittleElephantAndBoard.sample");

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

bool do_test(int M, int R, int G, int B, int __expected) {
    time_t startClock = clock();
    LittleElephantAndBoard *instance = new LittleElephantAndBoard();
    int __result = instance->getNumber(M, R, G, B);
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
        int M;
        from_stream(M);
        int R;
        from_stream(R);
        int G;
        from_stream(G);
        int B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(M, R, G, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475389198;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "LittleElephantAndBoard (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
