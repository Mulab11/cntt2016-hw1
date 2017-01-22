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

class CentaurCompany {
    public:
        struct Edge{int t,next;} G[105];int head[105],e;
        int pre[105],queue[105];
        long long dp[40][40][40][2],bag[40][40],tmp[40][40];
        double getvalue(vector<int> X, vector<int> Y) {
            memset(head,0,sizeof(head)),e=1;
            int n=X.size()+1;
            for (int i=0;i<n-1;i++){
                int x=X[i],y=Y[i];
                G[++e].t=y,G[e].next=head[x],head[x]=e;
                G[++e].t=x,G[e].next=head[y],head[y]=e;
            }
            pre[queue[1]=1]=0;
            for (int x,l=1,r=1;l<=r;l++) for (int i=head[x=queue[l]];i;i=G[i].next) if (G[i].t!=pre[x]) pre[queue[++r]=G[i].t]=x;
            memset(dp,0,sizeof(dp));
            for (int x,l=n;l;l--){
                x=queue[l];
                //printf("%d %d\n",l,x);
                dp[x][0][0][1]=1;
                for (int i=head[x];i;i=G[i].next) if (G[i].t!=pre[x]){
                    memset(bag,0,sizeof(bag));
                    for (int j=n;~j;j--) for (int k=n;~k;k--) if (dp[G[i].t][j][k][1]){
                        for (int a=n;a>=j;a--) for (int b=n;b>=k;b--) if (dp[x][a-j][b-k][1]) bag[a][b]+=dp[x][a-j][b-k][1]*dp[G[i].t][j][k][1];
                    }
                    for (int j=0;j<=n;j++) for (int k=0;k<=n;k++) dp[x][j][k][1]=bag[j][k];
                }
                for (int i=n;~i;i--) for (int j=n;~j;j--) dp[x][i][j][1]=i?dp[x][i-1][j][1]:0;
                for (int i=n;~i;i--) for (int j=n;~j;j--) dp[x][i][j][0]=j?dp[x][i][j-1][1]:0;
                memset(tmp,0,sizeof(tmp));
                tmp[0][0]=1;
                for (int i=head[x];i;i=G[i].next) if (G[i].t!=pre[x]){
                    memset(bag,0,sizeof(bag));
                    for (int j=n;~j;j--) for (int k=n;~k;k--) if (dp[G[i].t][j][k][0]){
                        for (int a=n;a>=j;a--) for (int b=n;b>=k;b--) if (tmp[a-j][b-k]) bag[a][b]+=tmp[a-j][b-k]*dp[G[i].t][j][k][0];
                    }
                    for (int j=0;j<=n;j++) for (int k=0;k<=n;k++) tmp[j][k]=bag[j][k];
                }
                //for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) if (tmp[i][j]) printf("tmp: %d %d %d %lld\n",x,i,j,tmp[i][j]);
                for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) for (int f=0;f<2;f++) dp[x][i][j][f]+=tmp[i][j];
                //for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) for (int f=0;f<2;f++) if (dp[x][i][j][f]) printf("%d %d %d %d %lld\n",x,i,j,f,dp[x][i][j][f]);
            }
            long long ans=0;
            for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) if (dp[1][i][j][0]) ans+=dp[1][i][j][0]*max(2*j-i-2,0);
            return 2.0*ans/(1ll<<n);
        }
};

// CUT begin
ifstream data("CentaurCompany.sample");

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

bool do_test(vector<int> a, vector<int> b, double __expected) {
    time_t startClock = clock();
    CentaurCompany *instance = new CentaurCompany();
    double __result = instance->getvalue(a, b);
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
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1483630515;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CentaurCompany (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
