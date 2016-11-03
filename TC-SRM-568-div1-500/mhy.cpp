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
template <typename T> inline void tension(T &a,const T &b){if (a>b) a=b;}
template <typename T> inline void relax(T &a,const T &b){if (a<b) a=b;}
const int mod=1000000007;

class EqualSums {
    public:
        struct Edge{int t,next,v;} G[105*105];int head[105],e;
        inline void add_edge(int x,int y,int z){
            G[++e].t=y,G[e].next=head[x],head[x]=e;G[e].v=z;
            G[++e].t=x,G[e].next=head[y],head[y]=e;G[e].v=-z;
        }
        int vis[105],queue[105],delta[105];
        int count(vector<string> board) {
            //这里是算法二
            memset(head,0,sizeof(head)),e=1;
            int n=board.size();
            for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (board[i][j]!='-') add_edge(j+n,i,board[i][j]-'0');
            memset(vis,0,sizeof(vis));
            int ans=1,zeroans=1;
            for (int root=0;root<n<<1;root++) if (!vis[root]){//枚举连通块
                int q,L,R;
                vis[queue[1]=root]=1,delta[root]=0;
                for (int x,l=1,&r=q=1;l<=r;l++) for (int i=head[x=queue[l]];i;i=G[i].next) if (!vis[G[i].t])
                    vis[queue[++r]=G[i].t]=1,delta[G[i].t]=delta[x]+G[i].v;
                else if (delta[G[i].t]!=delta[x]+G[i].v) return 0;//条件矛盾
                L=-0x3f3f3f3f,R=0x3f3f3f3f;
                for (int x,l=1;l<=q;l++) if ((x=queue[l])<n) relax(L,-delta[x]); else tension(R,-delta[x]);//解方程
                if (L>R) return 0;
                ans=1ll*ans*(R-L+1)%mod;
                L=-0x3f3f3f3f,R=0x3f3f3f3f;
                for (int x,l=1;l<=q;l++) if ((x=queue[l])<n) relax(L,1-delta[x]); else tension(R,-delta[x]);//计算min{b}>0的情况
                zeroans=1ll*zeroans*(R-L+1)%mod;
            }
            return (ans+mod-zeroans)%mod;
        }
};

// CUT begin
ifstream data("EqualSums.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    EqualSums *instance = new EqualSums();
    int __result = instance->count(board);
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
        vector<string> board;
        from_stream(board);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1475163259;
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
        cout << "EqualSums (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
