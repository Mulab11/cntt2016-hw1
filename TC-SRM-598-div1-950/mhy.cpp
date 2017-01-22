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

class TPS {
    public:
        static const int MAXV=10005,MAXE=10005;
        struct Edge{int t,next;} G[MAXE];int head[MAXV],e;
        inline void add_edge(int x,int y){G[++e].t=y,G[e].next=head[x],head[x]=e;}
        int queue[MAXV],pre[MAXV],dp[MAXV];
        int minimalBeacons(vector<string> linked) {
            memset(head,0,sizeof(head)),e=1;
            int n=linked.size();
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (linked[i][j]=='Y') add_edge(i+1,j+1);
            int ans=n-1;
            for (int root=1;root<=n;root++){
                pre[queue[1]=root]=0;
                for (int x,l=1,r=1;l<=r;l++) for (int i=head[x=queue[l]];i;i=G[i].next) if (G[i].t!=pre[x]) pre[queue[++r]=G[i].t]=x;
                for (int x,l=n;l;l--){
                    x=queue[l];
                    dp[x]=0;
                    int flag=0;
                    for (int i=head[x];i;i=G[i].next) if (G[i].t!=pre[x]) dp[x]+=max(dp[G[i].t],1),flag|=dp[G[i].t]==0;
                    dp[x]-=flag==1;
                    //printf("%d %d %d\n",root,x,dp[x]);
                }
                //printf("%d %d\n",root,dp[root]);
                if (dp[root]+1<ans) ans=dp[root]+1;
            }
            return ans;
        }
};

// CUT begin
ifstream data("TPS.sample");

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

bool do_test(vector<string> linked, int __expected) {
    time_t startClock = clock();
    TPS *instance = new TPS();
    int __result = instance->minimalBeacons(linked);
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
        vector<string> linked;
        from_stream(linked);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(linked, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1480509913;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TPS (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
