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

class ConversionMachine {
    public:
        static const int mod=1000000007;
        struct Matrix{
            int n,m;
            int a[105][105];
            Matrix(int n,int m):n(n),m(m){}
            void init0(){for (int i=0;i<n;i++) for (int j=0;j<m;j++) a[i][j]=0;}
            friend inline Matrix operator *(const Matrix &a,const Matrix &b){
                Matrix c(a.n,b.m);c.init0();
                for (int i=0;i<a.n;i++)
                    for (int j=0;j<a.m;j++) if (a.a[i][j])
                        for (int k=0;k<b.m;k++) if (b.a[j][k])
                            c.a[i][k]=(c.a[i][k]+1ll*a.a[i][j]*b.a[j][k])%mod;
                return c;
            }
        };
        int id[105][105];
        int countAll(string word1, string word2, vector<int> costs, int _maxCost) {
            long long maxCost=_maxCost;
            int n=word1.size(),c1=0,c2=0,m=1,N=0;
            for (int i=0;i<n;i++){
                int d=0;
                for (int j=word1[i]-'a';j!=word2[i]-'a';d++,maxCost-=costs[j],j=(j+1)%3) m++;
                if (d==1) c1++;
                if (d==2) c2++;
            }
            if (maxCost<0) return 0;
            m+=maxCost/(costs[0]+costs[1]+costs[2])*3;
            //printf("%d %d %d\n",c1,c2,m);
            for (int i=0;i<=n;i++) for (int j=0;i+j<=n;j++) id[i][j]=N++;N++;
            Matrix X(N,N);X.init0();
            for (int i=0;i<=n;i++) for (int j=0;i+j<=n;j++){
                int k=n-i-j;
                if (i) X.a[id[i][j]][id[i-1][j]]+=i;
                if (j) X.a[id[i][j]][id[i+1][j-1]]+=j;
                if (k) X.a[id[i][j]][id[i][j+1]]+=k;
            }
            X.a[id[0][0]][N-1]=X.a[N-1][N-1]=1;
            Matrix ans(1,N);ans.init0();
            ans.a[0][id[c1][c2]]=1;
            for (;m;m>>=1,X=X*X) if (m&1) ans=ans*X;
            return ans.a[0][N-1];
        }
};

// CUT begin
ifstream data("ConversionMachine.sample");

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

bool do_test(string word1, string word2, vector<int> costs, int maxCost, int __expected) {
    time_t startClock = clock();
    ConversionMachine *instance = new ConversionMachine();
    int __result = instance->countAll(word1, word2, costs, maxCost);
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
        string word1;
        from_stream(word1);
        string word2;
        from_stream(word2);
        vector<int> costs;
        from_stream(costs);
        int maxCost;
        from_stream(maxCost);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(word1, word2, costs, maxCost, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484325751;
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
        cout << "ConversionMachine (850 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
