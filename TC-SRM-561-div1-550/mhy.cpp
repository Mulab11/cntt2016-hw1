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

template <typename T> inline T sqr(const T &x){return x*x;}

struct Edge{int t,next;} G[105];int head[105],e;
inline void add_edge(int x,int y){G[++e].t=y,G[e].next=head[x],head[x]=e;}

class CirclesGame {
    public:
        int queue[105],pre[105],dp[105];
        int vis[1<<8];
        void dfs(int x,int v){
            for (int i=head[x];i;i=G[i].next) v^=dp[G[i].t];
            vis[v]=1;
            for (int i=head[x];i;i=G[i].next) dfs(G[i].t,v^dp[G[i].t]);
        }
        string whoCanWin(vector<int> x, vector<int> y, vector<int> r) {
            memset(head,0,sizeof(head)),e=1;
            memset(pre,-1,sizeof(pre));
            int n=x.size();
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (r[i]<r[j]&&r[j]>r[i]+sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]))&&(pre[i]<0||r[j]<r[pre[i]])) pre[i]=j;
            for (int i=0;i<n;i++) add_edge(~pre[i]?pre[i]:n,i);
            queue[1]=n;
            for (int x,l=1,r=1;l<=r;l++) for (int i=head[x=queue[l]];i;i=G[i].next) queue[++r]=G[i].t;
            for (int x,l=n+1;l;l--){
                memset(vis,0,sizeof(vis));
                dfs(x=queue[l],0);
                for (dp[x]=0;vis[dp[x]];dp[x]++);
            }
            int ans=0;
            for (int i=head[n];i;i=G[i].next) ans^=dp[G[i].t];
            return ans?"Alice":"Bob";
        }
};

// CUT begin
ifstream data("CirclesGame.sample");

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

bool do_test(vector<int> x, vector<int> y, vector<int> r, string __expected) {
    time_t startClock = clock();
    CirclesGame *instance = new CirclesGame();
    string __result = instance->whoCanWin(x, y, r);
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
        vector<int> r;
        from_stream(r);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, r, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475294416;
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
        cout << "CirclesGame (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
